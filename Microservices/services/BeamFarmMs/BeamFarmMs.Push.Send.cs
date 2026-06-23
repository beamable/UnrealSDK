using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
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
		/// Sends a remote push to every device the calling player has registered.
		/// The easiest end-to-end demo: register on a device, then call this from the
		/// same device. Requires a physical iOS device (APNs does not deliver to the
		/// Simulator) and valid APNs credentials in Realm Config.
		/// </summary>
		/// <param name="title">Notification title.</param>
		/// <param name="body">Notification body.</param>
		/// <param name="deepLink">Optional deep-link URL carried in the payload (the app opens it on tap).</param>
		[ClientCallable]
		public Task<SendResult> SendPushToSelf(string title, string body, string deepLink)
		{
			return DeliverToPlayer(Context.UserId, title, body, deepLink);
		}

		/// <summary>
		/// Back-office endpoint: send a remote push to a specific player by id. Exposed as
		/// <c>[ServerCallable]</c> so the Portal extension can call it — that still requires the
		/// "<c>*</c>" (admin) scope, but unlike <c>[AdminOnlyCallable]</c> it does not require a
		/// logged-in player, which a Portal extension's session does not carry.
		/// </summary>
		[ServerCallable]
		public async Task<AdminSendResult> SendPushToPlayer(long playerId, string title, string body, string deepLink)
		{
			var r = await DeliverToPlayer(playerId, title, body, deepLink);
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
		/// Portal extension to pick a recipient for <see cref="SendPushToPlayer"/>.
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

				result.players.Add(new RegisteredPlayer
				{
					playerId = id,
					deviceCount = devices.Count,
					platforms = devices.Select(d => NormalizePlatform(d.platform)).Distinct().ToList(),
					lastUpdated = devices.Max(d => d.updatedAt),
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

		private async Task<SendResult> DeliverToPlayer(long playerId, string title, string body, string deepLink)
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
			var message = new PushMessage { title = title, body = body, deepLink = deepLink };
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

	/// <summary>The notification content to deliver.</summary>
	public class PushMessage
	{
		public string title;
		public string body;
		public string deepLink;
	}

	/// <summary>Outcome of a single device delivery (shared by every push provider).</summary>
	public class PushSendOutcome
	{
		public bool ok;
		public string reason;
		public bool tokenIsInvalid; // the provider says this token is dead → prune it
	}
}
