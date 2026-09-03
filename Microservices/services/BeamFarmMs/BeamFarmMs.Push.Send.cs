using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using System.Threading.Tasks;
using Beamable.Api.Analytics;
using Beamable.Common;
using Beamable.Common.Api.Stats;
using Beamable.Server;

namespace Beamable.BeamFarmMs
{
	/// <summary>
	/// The "send" half of the push feature — the registration half lives in
	/// <c>BeamFarmMs.Push.cs</c>. Delivers remote pushes to a player's registered devices
	/// through Apple's APNs (iOS) and Firebase Cloud Messaging (Android), plus the admin
	/// roster/diagnostic endpoints the Portal extension needs.
	///
	/// Each stored device carries a <see cref="DeviceInfo.platform"/> ("apns" or "fcm");
	/// <see cref="DeliverToPlayer"/> routes each one to the right client: <see cref="ApnsClient"/>
	/// (Apple, HTTP/2 + .p8 JWT) or <see cref="FcmClient"/> (Firebase HTTP v1 + service-account
	/// OAuth). The per-provider credentials live in Realm Config (Portal → Realm → Config) under
	/// the "<c>apns_push</c>" and "<c>fcm_push</c>" namespaces — see <see cref="ApnsSettings"/> and
	/// <see cref="FcmSettings"/>.
	///
	/// Ported from the ReactNative PushNotificationService sample.
	/// </summary>
	public partial class BeamFarmMs : Microservice
	{
		// "game"/"public"/"player" — the domain/access/objectType the public marker is stored under
		// (matches StatsDomainType.Game + StatsAccessType.Public + the "player" object type).
		private const string PushStatDomain = "game";
		private const string PushStatPublicAccess = "public";
		private const string PushStatPlayerType = "player";

		// Player profile stats (game.private), set by the game — surfaced in the admin roster.
		private const string GamePlatformStatKey = "THORIUM_GAME_PLATFORM";
		private const string GameDeviceStatKey = "THORIUM_GAME_DEVICE";

		/// <summary>Lists the calling player's registered devices (tokens are masked in the response).</summary>
		[ClientCallable]
		public async Task<DeviceList> ListMyDevices()
		{
			var devices = await LoadDevices(Context.UserId);
			return new DeviceList
			{
				devices = devices.Select(d => new DeviceInfo
				{
					token = Mask(d.token),
					platform = NormalizePlatform(d.platform),
					environment = d.environment,
					updatedAt = d.updatedAt,
				}).ToList(),
			};
		}

		/// <summary>
		/// Sends a remote push to every device the calling player has registered, carrying the
		/// §3.3 Notification Intent Data (campaign/node/offers/campaignData). The easiest
		/// end-to-end demo: register on a device, then call this from the same device. Requires a
		/// physical iOS device (APNs does not deliver to the Simulator) and valid APNs credentials
		/// in Realm Config. All campaign fields are optional — an empty request reduces to a plain
		/// title/body/deepLink push. When <c>campaignId</c> and <c>nodeId</c> are both present the
		/// microservice also emits a funnel "Sent" analytics event.
		/// </summary>
		[ClientCallable]
		public Task<SendResult> SendCampaignPushToSelf(PushCampaignRequest request)
		{
			request ??= new PushCampaignRequest();
			return DeliverToPlayer(Context.UserId, request.title, request.body, request.deepLink, request.ToContext());
		}

		/// <summary>
		/// Back-office endpoint: send a remote push to a specific player by id, carrying the §3.3
		/// Notification Intent Data. Exposed as <c>[ServerCallable]</c> so the Portal extension can
		/// call it — that still requires the "<c>*</c>" (admin) scope, but unlike
		/// <c>[AdminOnlyCallable]</c> it does not require a logged-in player, which a Portal
		/// extension's session does not carry. The target player id is supplied separately; the
		/// rest of the campaign context rides in <paramref name="request"/>. All campaign fields
		/// are optional; when <c>campaignId</c> + <c>nodeId</c> are present a funnel "Sent" event
		/// is emitted.
		/// </summary>
		[ServerCallable]
		public async Task<AdminSendResult> SendCampaignPushToPlayer(long playerId, PushCampaignRequest request)
		{
			request ??= new PushCampaignRequest();
			var r = await DeliverToPlayer(playerId, request.title, request.body, request.deepLink, request.ToContext());
			return new AdminSendResult
			{
				success = r.success,
				attempted = r.attempted,
				succeeded = r.succeeded,
				failed = r.failed,
				messages = r.messages,
			};
		}

		/// <summary>
		/// Admin/back-office endpoint: lists every player who has at least one registered
		/// device, with a small summary (device count, platforms, last-updated). Used by the
		/// Portal extension to pick a recipient for <see cref="SendCampaignPushToPlayer"/>.
		///
		/// Private per-player stats aren't enumerable, so we find the roster by searching the
		/// public marker stat (<c>push_devices != 0</c>) that <c>SaveDevices</c> keeps in sync,
		/// then load each player's private device list for the summary. Tokens are never returned.
		/// </summary>
		[ServerCallable]
		public async Task<RegisteredPlayerList> ListRegisteredPlayers()
		{
			// SearchStats lives on the concrete AbsStatsApi (admin-only), not the IStatsApi
			// interface that Services.Stats is typed as — so cast to reach it.
			if (Services.Stats is not AbsStatsApi search)
				return new RegisteredPlayerList { message = "Stats search is unavailable in this runtime." };

			// Stat search compares values as STRINGS, so a numeric "gt 0" never matches the
			// string-stored count. Use a string "neq 0" to select every player whose marker
			// is a non-zero count (the "0" markers left by a full unregister are excluded).
			var response = await search.SearchStats(
				PushStatDomain, PushStatPublicAccess, PushStatPlayerType,
				new List<Criteria> { new Criteria(PublicMarkerStatKey, "neq", "0") });

			var ids = response?.ids ?? Array.Empty<long>();
			var result = new RegisteredPlayerList();

			foreach (var id in ids)
			{
				var devices = await LoadDevices(id);
				if (devices.Count == 0) continue; // marker lagged behind a prune — skip

				// The player's game platform/device come from their private profile stats
				// (set by the game), not from push registration. Missing → empty string.
				var profile = await Services.Stats.GetFilteredStats(
					StatsDomainType.Game, StatsAccessType.Private, id,
					new[] { GamePlatformStatKey, GameDeviceStatKey });

				result.players.Add(new RegisteredPlayer
				{
					playerId = id,
					deviceCount = devices.Count,
					platforms = devices.Select(d => NormalizePlatform(d.platform)).Distinct().ToList(),
					lastUpdated = devices.Max(d => d.updatedAt),
					gamePlatform = profile.GetValueOrDefault(GamePlatformStatKey, ""),
					gameDevice = profile.GetValueOrDefault(GameDeviceStatKey, ""),
				});
			}

			return result;
		}

		/// <summary>
		/// Admin/diagnostic endpoint: verifies that <c>fcm_push.service_account_json</c> in Realm
		/// Config parses and that the private key actually loads — handy right after pasting the
		/// JSON into the Portal, since a mangled <c>private_key</c> is the usual failure. Returns a
		/// secret-free summary and never echoes the key. Also logs the same summary server-side.
		/// </summary>
		[ServerCallable]
		public async Task<FcmConfigStatus> CheckFcmConfig()
		{
			try
			{
				var settings = await LoadFcmSettings(); // also logs the safe summary
				FcmClient.EnsureKeyLoads(settings);     // throws if the RSA key can't be parsed
				return new FcmConfigStatus
				{
					configured = true,
					privateKeyLoaded = true,
					projectId = settings.ProjectId,
					clientEmail = settings.ClientEmail,
					tokenUri = settings.TokenUri,
					message = "fcm_push.service_account_json parsed and the private key loaded successfully.",
				};
			}
			catch (Exception ex)
			{
				BeamableLogger.LogWarning("FCM config check failed: {msg}", ex.Message);
				return new FcmConfigStatus { configured = false, privateKeyLoaded = false, message = ex.Message };
			}
		}

		// --- Internals ------------------------------------------------------

		private async Task<SendResult> DeliverToPlayer(long playerId, string title, string body, string deepLink, PushCampaignContext campaign = null)
		{
			if (string.IsNullOrWhiteSpace(title) && string.IsNullOrWhiteSpace(body))
				return new SendResult { success = false, attempted = 0, succeeded = 0, failed = 0, messages = { "title or body is required." } };

			var devices = await LoadDevices(playerId);
			var result = new SendResult { attempted = devices.Count };

			if (devices.Count == 0)
			{
				result.success = false;
				result.messages.Add($"Player {playerId} has no registered devices.");
				return result;
			}

			var apns = new ApnsClient();
			var fcm = new FcmClient();

			// The §3.3 Notification Intent Data, embedded in the provider payload (FCM data / APNs
			// userInfo). gamerTag defaults to the target player id when the caller didn't set it,
			// and cidPid defaults to this microservice's own realm scope ("<cid>.<pid>") so the
			// funnel "Sent" event always carries the cidPid the device-side Received/Opened stages
			// join on (they require it). The caller may still override it.
			campaign ??= new PushCampaignContext();
			var message = new PushMessage
			{
				title = title,
				body = body,
				deepLink = deepLink,
				campaignId = campaign.campaignId,
				nodeId = campaign.nodeId,
				gamerTag = string.IsNullOrWhiteSpace(campaign.gamerTag) ? playerId.ToString() : campaign.gamerTag,
				accountId = campaign.accountId,
				cidPid = string.IsNullOrWhiteSpace(campaign.cidPid) ? $"{Context.Cid}.{Context.Pid}" : campaign.cidPid,
				offers = campaign.offers,
				campaignData = campaign.campaignData,
			};
			var stale = new List<string>();

			// Provider settings are resolved lazily and cached for this call, so a player with
			// only FCM devices never fails on a missing apns_push config (and vice versa). A
			// missing config for one provider surfaces as a per-device message, not a hard abort.
			var apnsLoaded = false; ApnsSettings apnsSettings = null; string apnsError = null;
			async Task<(ApnsSettings settings, string error)> GetApns()
			{
				if (!apnsLoaded)
				{
					apnsLoaded = true;
					try { apnsSettings = await LoadApnsSettings(); }
					catch (Exception ex) { apnsError = $"APNs not configured: {ex.Message}"; }
				}
				return (apnsSettings, apnsError);
			}

			var fcmLoaded = false; FcmSettings fcmSettings = null; string fcmError = null;
			async Task<(FcmSettings settings, string error)> GetFcm()
			{
				if (!fcmLoaded)
				{
					fcmLoaded = true;
					try { fcmSettings = await LoadFcmSettings(); }
					catch (Exception ex) { fcmError = $"FCM not configured: {ex.Message}"; }
				}
				return (fcmSettings, fcmError);
			}

			foreach (var device in devices)
			{
				PushSendOutcome outcome;
				if (NormalizePlatform(device.platform) == PushPlatform.Fcm)
				{
					var (settings, error) = await GetFcm();
					outcome = settings != null
						? await fcm.Send(settings, device, message)
						: new PushSendOutcome { ok = false, reason = error };
				}
				else
				{
					var (settings, error) = await GetApns();
					outcome = settings != null
						? await apns.Send(settings, device, message)
						: new PushSendOutcome { ok = false, reason = error };
				}

				if (outcome.ok)
				{
					result.succeeded++;
				}
				else
				{
					result.failed++;
					result.messages.Add($"{Mask(device.token)}: {outcome.reason}");
					if (outcome.tokenIsInvalid) stale.Add(device.token);
				}
			}

			// Funnel "Sent" event, emitted ONCE per (player, send) once at least one device send
			// succeeded — not once per device. Only fires when the message carries both campaignId
			// and nodeId (tracked-campaign rule); otherwise the push is untracked and we skip silently.
			if (result.succeeded > 0)
				EmitSentEvent(playerId, message);

			// The provider told us these tokens are dead (APNs Unregistered/BadDeviceToken,
			// FCM UNREGISTERED/INVALID_ARGUMENT) — prune them so we stop delivering to them.
			if (stale.Count > 0)
			{
				devices.RemoveAll(d => stale.Contains(d.token));
				await SaveDevices(playerId, devices);
				result.messages.Add($"Pruned {stale.Count} invalid token(s).");
			}

			result.success = result.succeeded > 0;
			return result;
		}

		/// <summary>
		/// Emits a funnel "Sent" <see cref="CoreEvent"/> via <c>Services.Analytics</c>, once per
		/// logical send (once at least one of the player's devices accepted the push) — not once
		/// per device. Fires only when the message carries both <c>campaignId</c> and <c>nodeId</c>;
		/// an untracked push is skipped silently.
		///
		/// The event is a <c>CoreEvent</c> (category "notification_funnel", eventName "Sent") whose
		/// params are: campaignId, nodeId, gamerTag (the target player), accountId, cidPid, offerData
		/// (the SINGLE relevant offer — the first one this message carried, if any), deeplink,
		/// funnelType="Sent". Empty fields are omitted to keep the payload flat. The send is
		/// fire-and-forget (the analytics service queues it) and best-effort — a failure to queue
		/// the funnel event never fails a successful push.
		/// </summary>
		private void EmitSentEvent(long playerId, PushMessage message)
		{
			// Only track campaigns that carry both ids.
			if (string.IsNullOrWhiteSpace(message.campaignId) || string.IsNullOrWhiteSpace(message.nodeId))
				return;

			var gamerTag = string.IsNullOrWhiteSpace(message.gamerTag) ? playerId.ToString() : message.gamerTag;

			var p = new Dictionary<string, object>
			{
				["campaignId"] = message.campaignId,
				["nodeId"] = message.nodeId,
				["gamerTag"] = gamerTag,
				["funnelType"] = "Sent",
			};
			if (!string.IsNullOrWhiteSpace(message.accountId)) p["accountId"] = message.accountId;
			if (!string.IsNullOrWhiteSpace(message.cidPid)) p["cidPid"] = message.cidPid;
			if (!string.IsNullOrWhiteSpace(message.deepLink)) p["deeplink"] = message.deepLink;

			// offerData is a SINGLE offer. A push can carry several; we report the first one as the
			// offer this Sent event concerns (one Sent per logical send, not per device). Omitted
			// entirely when the message has no offers. Match the device-side funnel builders: OMIT
			// absent fields rather than emit explicit nulls.
			var offer = message.offers?.FirstOrDefault();
			if (offer != null)
			{
				var offerData = new Dictionary<string, object>();
				if (!string.IsNullOrWhiteSpace(offer.itemId)) offerData["itemId"] = offer.itemId;
				if (!string.IsNullOrWhiteSpace(offer.value)) offerData["value"] = offer.value;
				if (!string.IsNullOrWhiteSpace(offer.customData)) offerData["customData"] = offer.customData;
				p["offerData"] = offerData;
			}

			try
			{
				var ev = new CoreEvent("notification_funnel", "Sent", p);
				Services.Analytics.SendAnalyticsEvent(Services.Analytics.BuildRequest(ev));
			}
			catch (Exception ex)
			{
				// Analytics is best-effort — never fail a successful push because the funnel
				// event couldn't be queued.
				BeamableLogger.LogWarning("Failed to emit 'Sent' funnel event for player {player}: {msg}", playerId, ex.Message);
			}
		}

		/// <summary>Reads the APNs credentials from this realm's config (the "apns_push" namespace).</summary>
		private async Task<ApnsSettings> LoadApnsSettings()
		{
			var config = await Services.RealmConfig.GetRealmConfigSettings();
			var ns = config.GetNamespace(ApnsSettings.Namespace);
			return ApnsSettings.FromGetter(key => ns.GetSetting(key));
		}

		/// <summary>Reads the FCM credentials from this realm's config (the "fcm_push" namespace).</summary>
		private async Task<FcmSettings> LoadFcmSettings()
		{
			var config = await Services.RealmConfig.GetRealmConfigSettings();
			var ns = config.GetNamespace(FcmSettings.Namespace);
			var settings = FcmSettings.FromGetter(key => ns.GetSetting(key));
			// Secret-free confirmation that the pasted JSON parsed (no private key in the log).
			BeamableLogger.Log("FCM config loaded from Realm Config: {summary}", settings.DescribeSafely());
			return settings;
		}

		private static string Mask(string token)
		{
			if (string.IsNullOrEmpty(token)) return token;
			return token.Length <= 12 ? token : $"{token[..8]}…{token[^4..]}";
		}
	}

	/// <summary>The calling player's registered devices.</summary>
	[Serializable]
	public class DeviceList
	{
		public List<DeviceInfo> devices = new();
	}

	/// <summary>Aggregated outcome of a send across one player's device(s).</summary>
	[Serializable]
	public class SendResult
	{
		public bool success;
		public int attempted;
		public int succeeded;
		public int failed;
		public List<string> messages = new();
	}

	/// <summary>
	/// Admin send result. Same shape as <see cref="SendResult"/> but a distinct type
	/// so the admin endpoint generates its own client return type (the web-client
	/// generator emits one return type per endpoint, so two endpoints sharing one type
	/// would produce a duplicate declaration).
	/// </summary>
	[Serializable]
	public class AdminSendResult
	{
		public bool success;
		public int attempted;
		public int succeeded;
		public int failed;
		public List<string> messages = new();
	}

	/// <summary>A player who has at least one registered device (no token is exposed).</summary>
	[Serializable]
	public class RegisteredPlayer
	{
		public long playerId;
		public int deviceCount;
		public List<string> platforms = new(); // distinct: "apns" and/or "fcm"
		public long lastUpdated;               // newest device's updatedAt (unix seconds)
		public string gamePlatform;            // THORIUM_GAME_PLATFORM (e.g. "Web"), "" if unset
		public string gameDevice;              // THORIUM_GAME_DEVICE (e.g. "Desktop"), "" if unset
	}

	/// <summary>The roster of players with registered devices, for the admin Portal tool.</summary>
	[Serializable]
	public class RegisteredPlayerList
	{
		public List<RegisteredPlayer> players = new();
		public string message; // set only when the roster couldn't be produced
	}

	/// <summary>
	/// Secret-free result of <c>CheckFcmConfig</c>. Confirms the pasted service-account JSON
	/// parsed and the private key loaded; <see cref="message"/> carries the reason on failure.
	/// The private key is never included.
	/// </summary>
	[Serializable]
	public class FcmConfigStatus
	{
		public bool configured;
		public bool privateKeyLoaded;
		public string projectId;
		public string clientEmail;
		public string tokenUri;
		public string message;
	}

	/// <summary>
	/// A single offer carried by a campaign push (§3.3 <c>offers[]</c>). <see cref="customData"/>
	/// is free-form (typed <c>T</c> at the SDK layer) and travels as opaque JSON across the
	/// native bridge, so it is modeled here as a JSON object string.
	/// </summary>
	[Serializable]
	public class PushOffer
	{
		public string itemId;
		public string value;        // "string|number" in the schema — carried as a string on the wire
		public string customData;   // free-form JSON object, as a string (e.g. {"k":"v"})
	}

	/// <summary>
	/// §3.3 Notification Intent Data carried by a campaign push, plus the notification content.
	/// This is the request object for <see cref="BeamFarmMs.SendCampaignPushToSelf"/> and
	/// <see cref="BeamFarmMs.SendCampaignPushToPlayer"/>. All campaign fields are optional —
	/// supplying none reduces to a plain title/body/deepLink push (no funnel event). Embedded into
	/// the provider payload as the flat stringified §3.3 map; when <c>campaignId</c> +
	/// <c>nodeId</c> are present the microservice also emits a "Sent" funnel event.
	/// </summary>
	[Serializable]
	public class PushCampaignRequest
	{
		public string title;
		public string body;
		public string deepLink;          // canonical key on the wire: "deeplink"

		public string campaignId;        // §3.3
		public string nodeId;            // §3.3
		public string gamerTag;          // Beamable dbid; defaults to the target player id when unset
		public string accountId;         // Beamable account id
		public string cidPid;            // "<cid>.<pid>" realm scope
		public List<PushOffer> offers;   // optional offers array
		public string campaignData;      // free-form JSON object, as a string

		/// <summary>Projects the schema fields (sans title/body/deepLink) into the internal context.</summary>
		public PushCampaignContext ToContext() => new PushCampaignContext
		{
			campaignId = campaignId,
			nodeId = nodeId,
			gamerTag = gamerTag,
			accountId = accountId,
			cidPid = cidPid,
			offers = offers,
			campaignData = campaignData,
		};
	}

	/// <summary>
	/// Internal carrier for the §3.3 campaign context handed to <c>DeliverToPlayer</c> (not a
	/// callable surface). Mirrors the schema fields of <see cref="PushCampaignRequest"/> minus the
	/// notification content.
	/// </summary>
	[Serializable]
	public class PushCampaignContext
	{
		public string campaignId;
		public string nodeId;
		public string gamerTag;
		public string accountId;
		public string cidPid;
		public List<PushOffer> offers;
		public string campaignData;
	}

	/// <summary>
	/// The notification content to deliver, plus the optional §3.3 Notification Intent Data
	/// (campaign context). All campaign fields are additive/optional — a plain title/body/deepLink
	/// message (the original shape) keeps working unchanged.
	///
	/// On the wire the schema is embedded as a FLAT string→string map: scalars as plain strings,
	/// <see cref="offers"/> and <see cref="campaignData"/> as JSON-encoded strings — into FCM
	/// <c>data</c> and APNs <c>userInfo</c> identically.
	/// </summary>
	public class PushMessage
	{
		public string title;
		public string body;
		public string deepLink;     // canonical key: "deeplink"

		// --- §3.3 Notification Intent Data (all optional) ---
		public string campaignId;
		public string nodeId;
		public string gamerTag;     // Beamable dbid (the target player)
		public string accountId;
		public string cidPid;       // "<cid>.<pid>" realm scope
		public List<PushOffer> offers;          // optional array
		public string campaignData; // free-form JSON object, as a string

		/// <summary>
		/// Builds the §3.3 Notification Intent Data as a flat string→string map: scalar fields as
		/// plain strings; <see cref="offers"/> and <see cref="campaignData"/> as JSON-encoded
		/// strings. The canonical deeplink key is <c>deeplink</c>. Empty/null fields are omitted so
		/// an un-tagged message produces an empty map (and a plain message stays byte-identical to
		/// the old payload aside from the existing deeplink key). Used for both FCM <c>data</c> and
		/// APNs <c>userInfo</c> so engine code is identical.
		/// </summary>
		public void WriteIntentData(IDictionary<string, object> map)
		{
			if (!string.IsNullOrWhiteSpace(campaignId)) map["campaignId"] = campaignId;
			if (!string.IsNullOrWhiteSpace(nodeId)) map["nodeId"] = nodeId;
			if (!string.IsNullOrWhiteSpace(gamerTag)) map["gamerTag"] = gamerTag;
			if (!string.IsNullOrWhiteSpace(accountId)) map["accountId"] = accountId;
			if (!string.IsNullOrWhiteSpace(cidPid)) map["cidPid"] = cidPid;
			if (!string.IsNullOrWhiteSpace(deepLink)) map["deeplink"] = deepLink;

			if (offers != null && offers.Count > 0)
				map["offers"] = JsonSerializer.Serialize(offers);

			// campaignData is already a JSON object string — passed through verbatim.
			if (!string.IsNullOrWhiteSpace(campaignData)) map["campaignData"] = campaignData;
		}
	}

	/// <summary>Outcome of a single device delivery (shared by every push provider).</summary>
	public class PushSendOutcome
	{
		public bool ok;
		public string reason;
		public bool tokenIsInvalid; // the provider says this token is dead → prune it
	}
}
