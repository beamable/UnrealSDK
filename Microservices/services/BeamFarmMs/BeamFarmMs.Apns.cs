using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Http;
using System.Security.Cryptography;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Server;

namespace Beamable.BeamFarmMs
{
	/// <summary>Which APNs environment a device's token belongs to.</summary>
	public static class ApnsEnvironment
	{
		public const string Sandbox = "sandbox";
		public const string Production = "production";

		/// <summary>The APNs host for an environment.</summary>
		public static string HostFor(string environment) =>
			environment == Sandbox ? "api.sandbox.push.apple.com" : "api.push.apple.com";
	}

	/// <summary>
	/// APNs token-based-auth credentials, read from Realm Config.
	///
	/// Set these in Portal → your Realm → Config, under the namespace
	/// "<c>apns_push</c>":
	///   • <c>auth_key</c>      — contents of your AuthKey_XXXX.p8 file (the full PEM,
	///                            "-----BEGIN PRIVATE KEY-----" … included).
	///   • <c>key_id</c>        — the 10-char Key ID of that .p8 key.
	///   • <c>team_id</c>       — your 10-char Apple Developer Team ID.
	///   • <c>bundle_id</c>     — the app's bundle id (used as the APNs topic).
	///   • <c>default_environment</c> — optional: "sandbox" (default) or "production".
	///
	/// Keeping these in Realm Config (not in source) means the .p8 secret never
	/// ships in the repo or the client, and differs per realm.
	/// </summary>
	public class ApnsSettings
	{
		public string AuthKeyP8;
		public string KeyId;
		public string TeamId;
		public string BundleId;
		public string DefaultEnvironment;

		public const string Namespace = "apns_push";

		/// <summary>
		/// Resolves the APNs environment for a device — its own stored value, or the
		/// realm default when the device didn't specify one.
		/// </summary>
		public string ResolveEnvironment(string deviceEnvironment) =>
			!string.IsNullOrWhiteSpace(deviceEnvironment) ? deviceEnvironment : DefaultEnvironment;

		/// <summary>
		/// Builds and validates the credentials from a setting getter (typically the
		/// realm-config namespace's <c>GetSetting</c>). Throws if a required value is
		/// missing so the caller can surface a clear "not configured" error.
		/// </summary>
		public static ApnsSettings FromGetter(Func<string, string> getSetting)
		{
			var settings = new ApnsSettings
			{
				AuthKeyP8 = getSetting("auth_key"),
				KeyId = getSetting("key_id"),
				TeamId = getSetting("team_id"),
				BundleId = getSetting("bundle_id"),
				DefaultEnvironment = NormalizeEnv(getSetting("default_environment")),
			};

			Require(settings.AuthKeyP8, "auth_key");
			Require(settings.KeyId, "key_id");
			Require(settings.TeamId, "team_id");
			Require(settings.BundleId, "bundle_id");

			return settings;
		}

		private static string NormalizeEnv(string raw)
		{
			if (string.IsNullOrWhiteSpace(raw)) return ApnsEnvironment.Sandbox;
			var e = raw.Trim().ToLowerInvariant();
			return e is "production" or "prod" ? ApnsEnvironment.Production : ApnsEnvironment.Sandbox;
		}

		private static void Require(string value, string key)
		{
			if (string.IsNullOrWhiteSpace(value))
				throw new Exception($"missing Realm Config '{Namespace}.{key}'");
		}
	}

	/// <summary>
	/// Sends notifications to Apple's APNs over HTTP/2 using token-based
	/// authentication (a JWT signed with your .p8 key — no per-push certificate).
	///
	/// The <see cref="HttpClient"/> and the signed provider JWT are cached in
	/// <c>static</c> fields: Apple throttles ("TooManyProviderTokenUpdates") if you
	/// mint a new JWT too often, and the token is valid for up to an hour, so we
	/// reuse one for ~50 minutes across every request and instance.
	/// </summary>
	public class ApnsClient
	{
		// One shared HTTP/2 client for the whole process.
		private static readonly HttpClient Http = new(new SocketsHttpHandler
		{
			// APNs supports many requests on one HTTP/2 connection; keep it warm.
			PooledConnectionIdleTimeout = TimeSpan.FromMinutes(10),
			EnableMultipleHttp2Connections = true,
		})
		{
			DefaultRequestVersion = HttpVersion.Version20,
			DefaultVersionPolicy = HttpVersionPolicy.RequestVersionExact,
		};

		// Cached provider JWT, guarded by JwtLock.
		private static readonly object JwtLock = new();
		private static string _cachedJwt;
		private static string _cachedJwtFingerprint;
		private static DateTimeOffset _jwtIssuedAt;
		private static readonly TimeSpan JwtLifetime = TimeSpan.FromMinutes(50);

		/// <summary>Sends one push to one device.</summary>
		public async Task<PushSendOutcome> Send(ApnsSettings settings, DeviceInfo device, PushMessage message)
		{
			string jwt;
			try
			{
				jwt = GetProviderToken(settings);
			}
			catch (Exception ex)
			{
				return new PushSendOutcome { ok = false, reason = $"failed to sign provider token: {ex.Message}" };
			}

			var environment = settings.ResolveEnvironment(device.environment);
			var url = $"https://{ApnsEnvironment.HostFor(environment)}/3/device/{device.token}";
			var payload = BuildPayload(message);

			using var request = new HttpRequestMessage(HttpMethod.Post, url)
			{
				Version = HttpVersion.Version20,
				VersionPolicy = HttpVersionPolicy.RequestVersionExact,
				Content = new StringContent(payload, Encoding.UTF8, "application/json"),
			};
			request.Headers.TryAddWithoutValidation("authorization", $"bearer {jwt}");
			request.Headers.TryAddWithoutValidation("apns-topic", settings.BundleId);
			request.Headers.TryAddWithoutValidation("apns-push-type", "alert");
			request.Headers.TryAddWithoutValidation("apns-priority", "10");

			try
			{
				using var response = await Http.SendAsync(request);
				if (response.StatusCode == HttpStatusCode.OK)
					return new PushSendOutcome { ok = true };

				var bodyText = await response.Content.ReadAsStringAsync();
				var reason = ExtractReason(bodyText) ?? response.StatusCode.ToString();
				var dead = response.StatusCode == HttpStatusCode.Gone // 410 Unregistered
					|| reason is "BadDeviceToken" or "Unregistered" or "DeviceTokenNotForTopic";

				BeamableLogger.LogWarning("APNs rejected push ({status}): {reason}", (int)response.StatusCode, reason);
				return new PushSendOutcome { ok = false, reason = reason, tokenIsInvalid = dead };
			}
			catch (Exception ex)
			{
				return new PushSendOutcome { ok = false, reason = $"transport error: {ex.Message}" };
			}
		}

		/// <summary>Builds the APNs JSON payload. Omits empty fields; carries an optional deep link.</summary>
		private static string BuildPayload(PushMessage message)
		{
			var alert = new Dictionary<string, object>();
			if (!string.IsNullOrWhiteSpace(message.title)) alert["title"] = message.title;
			if (!string.IsNullOrWhiteSpace(message.body)) alert["body"] = message.body;

			var aps = new Dictionary<string, object>
			{
				["alert"] = alert,
				["sound"] = "default",
				// Wake the Notification Service Extension on delivery — even when the app is
				// backgrounded/killed — so it can run closed-app analytics (the webhook POST).
				// Without "mutable-content": 1 the NSE never runs and the closed-app POST won't
				// fire (the alert still displays). Requires apns-push-type: alert (set above).
				["mutable-content"] = 1,
			};

			var root = new Dictionary<string, object> { ["aps"] = aps };

			// §3.3 Notification Intent Data goes in userInfo (the top-level keys alongside "aps"),
			// stringified to match Android's FCM data map exactly. This writes the canonical
			// "deeplink" key (the app already reads it tolerantly: deepLink/deeplink/deep_link).
			message.WriteIntentData(root);

			// Back-compat: keep the legacy "deepLink" key the original payload emitted.
			if (!string.IsNullOrWhiteSpace(message.deepLink))
				root["deepLink"] = message.deepLink; // the app reads this on tap to route

			return JsonSerializer.Serialize(root);
		}

		// --- Provider JWT ---------------------------------------------------

		private static string GetProviderToken(ApnsSettings settings)
		{
			var fingerprint = $"{settings.TeamId}:{settings.KeyId}";
			lock (JwtLock)
			{
				var fresh = _cachedJwt != null
					&& _cachedJwtFingerprint == fingerprint
					&& DateTimeOffset.UtcNow - _jwtIssuedAt < JwtLifetime;
				if (fresh) return _cachedJwt;

				_cachedJwt = SignProviderToken(settings);
				_cachedJwtFingerprint = fingerprint;
				_jwtIssuedAt = DateTimeOffset.UtcNow;
				return _cachedJwt;
			}
		}

		private static string SignProviderToken(ApnsSettings settings)
		{
			var header = $"{{\"alg\":\"ES256\",\"kid\":\"{settings.KeyId}\",\"typ\":\"JWT\"}}";
			var iat = DateTimeOffset.UtcNow.ToUnixTimeSeconds();
			var claims = $"{{\"iss\":\"{settings.TeamId}\",\"iat\":{iat}}}";

			var signingInput = $"{Base64Url(Encoding.UTF8.GetBytes(header))}.{Base64Url(Encoding.UTF8.GetBytes(claims))}";

			using var ecdsa = LoadKey(settings.AuthKeyP8);
			var signature = ecdsa.SignData(
				Encoding.UTF8.GetBytes(signingInput),
				HashAlgorithmName.SHA256,
				DSASignatureFormat.IeeeP1363FixedFieldConcatenation); // JWS needs raw r||s, not DER

			return $"{signingInput}.{Base64Url(signature)}";
		}

		/// <summary>Imports the .p8 (PKCS#8) key whether it's full PEM, escaped, or bare base64.</summary>
		private static ECDsa LoadKey(string authKey)
		{
			var key = authKey.Trim();
			// Realm Config UIs often store newlines as the literal characters "\n".
			if (key.Contains("\\n")) key = key.Replace("\\n", "\n");

			var ecdsa = ECDsa.Create();
			if (key.Contains("BEGIN"))
			{
				ecdsa.ImportFromPem(key);
			}
			else
			{
				// Bare base64 of the PKCS#8 DER (header/footer stripped).
				var der = Convert.FromBase64String(key.Replace("\n", "").Replace("\r", "").Trim());
				ecdsa.ImportPkcs8PrivateKey(der, out _);
			}
			return ecdsa;
		}

		private static string Base64Url(byte[] bytes) =>
			Convert.ToBase64String(bytes).TrimEnd('=').Replace('+', '-').Replace('/', '_');

		private static string ExtractReason(string apnsErrorBody)
		{
			if (string.IsNullOrWhiteSpace(apnsErrorBody)) return null;
			try
			{
				using var doc = JsonDocument.Parse(apnsErrorBody);
				return doc.RootElement.TryGetProperty("reason", out var r) ? r.GetString() : null;
			}
			catch
			{
				return null;
			}
		}
	}
}
