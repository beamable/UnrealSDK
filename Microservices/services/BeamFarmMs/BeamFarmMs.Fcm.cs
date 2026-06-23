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
	/// <summary>
	/// Firebase Cloud Messaging (FCM) credentials, read from Realm Config — the
	/// Android counterpart to <see cref="ApnsSettings"/>.
	///
	/// Set this in Portal → your Realm → Config, under the namespace
	/// "<c>fcm_push</c>":
	///   • <c>service_account_json</c> — the <b>full JSON</b> of a Firebase service
	///     account key (Firebase Console → Project Settings → Service Accounts →
	///     "Generate new private key"). It contains <c>project_id</c>,
	///     <c>client_email</c>, <c>private_key</c> and <c>token_uri</c>.
	///
	/// Storing the whole JSON in one key mirrors how APNs stores the full <c>.p8</c>
	/// PEM in <c>apns_push.auth_key</c>: the secret lives only in Realm Config, never
	/// in the repo or the client, and differs per realm. Unlike APNs there is no
	/// sandbox/production split — FCM has a single endpoint.
	/// </summary>
	public class FcmSettings
	{
		public string ProjectId;
		public string ClientEmail;
		public string PrivateKeyPem;
		public string TokenUri;

		public const string Namespace = "fcm_push";

		/// <summary>OAuth2 scope required to send messages through the FCM HTTP v1 API.</summary>
		public const string MessagingScope = "https://www.googleapis.com/auth/firebase.messaging";

		private const string DefaultTokenUri = "https://oauth2.googleapis.com/token";

		/// <summary>The FCM HTTP v1 "send" endpoint for this project.</summary>
		public string SendUrl => $"https://fcm.googleapis.com/v1/projects/{ProjectId}/messages:send";

		/// <summary>
		/// A secret-free, log-safe one-line summary of what parsed out of the pasted JSON —
		/// confirms project/email/key shape without ever revealing the private key.
		/// </summary>
		public string DescribeSafely()
		{
			var key = PrivateKeyPem ?? "";
			var looksLikePem = key.Contains("BEGIN") && key.Contains("PRIVATE KEY");
			return $"project_id='{ProjectId}', client_email='{ClientEmail}', token_uri='{TokenUri}', " +
				   $"private_key=[{(looksLikePem ? "PEM" : "NOT-PEM")}, {key.Length} chars]";
		}

		/// <summary>
		/// Builds and validates the credentials from a setting getter (typically the
		/// realm-config namespace's <c>GetSetting</c>). Reads the <c>service_account_json</c>
		/// blob, parses it, and throws a clear error if the blob is missing, unparseable,
		/// or missing a required field — so the caller can surface a "not configured"
		/// message instead of failing mid-send.
		/// </summary>
		public static FcmSettings FromGetter(Func<string, string> getSetting)
		{
			var json = getSetting("service_account_json");
			if (string.IsNullOrWhiteSpace(json))
				throw new Exception($"missing Realm Config '{Namespace}.service_account_json'");

			JsonElement root;
			try
			{
				using var doc = JsonDocument.Parse(json);
				root = doc.RootElement.Clone();
			}
			catch (Exception ex)
			{
				throw new Exception($"'{Namespace}.service_account_json' is not valid JSON: {ex.Message}");
			}

			var settings = new FcmSettings
			{
				ProjectId = ReadString(root, "project_id"),
				ClientEmail = ReadString(root, "client_email"),
				PrivateKeyPem = NormalizePem(ReadString(root, "private_key")),
				TokenUri = ReadString(root, "token_uri"),
			};

			if (string.IsNullOrWhiteSpace(settings.TokenUri))
				settings.TokenUri = DefaultTokenUri;

			Require(settings.ProjectId, "project_id");
			Require(settings.ClientEmail, "client_email");
			Require(settings.PrivateKeyPem, "private_key");

			return settings;
		}

		private static string ReadString(JsonElement root, string property) =>
			root.TryGetProperty(property, out var value) && value.ValueKind == JsonValueKind.String
				? value.GetString()
				: null;

		/// <summary>
		/// The service-account <c>private_key</c> embeds newlines as the literal
		/// characters "\n" inside the JSON string; turn them into real newlines so
		/// <see cref="System.Security.Cryptography.RSA.ImportFromPem"/> accepts the PEM.
		/// (Same normalization trick as <c>ApnsClient.LoadKey</c>.)
		/// </summary>
		private static string NormalizePem(string key)
		{
			if (string.IsNullOrWhiteSpace(key)) return key;
			key = key.Trim();
			return key.Contains("\\n") ? key.Replace("\\n", "\n") : key;
		}

		private static void Require(string value, string key)
		{
			if (string.IsNullOrWhiteSpace(value))
				throw new Exception($"'{Namespace}.service_account_json' is missing '{key}'");
		}
	}

	/// <summary>
	/// Sends notifications to Android (and any FCM client) through Firebase Cloud
	/// Messaging's HTTP v1 API — the Android counterpart to <see cref="ApnsClient"/>.
	///
	/// FCM has no per-push token like APNs. Instead we authenticate with a short-lived
	/// OAuth2 access token, obtained by signing a JWT (RS256) with the service account's
	/// private key and exchanging it at Google's token endpoint. Like the APNs provider
	/// JWT, the access token is valid for ~1 hour, so the <see cref="HttpClient"/> and the
	/// access token are cached in <c>static</c> fields and reused for ~50 minutes across
	/// every request and instance.
	/// </summary>
	public class FcmClient
	{
		// One shared client for the whole process. FCM is plain HTTPS (HTTP/1.1 is fine).
		private static readonly HttpClient Http = new(new SocketsHttpHandler
		{
			PooledConnectionIdleTimeout = TimeSpan.FromMinutes(10),
		});

		// Cached OAuth access token, guarded by TokenLock.
		private static readonly object TokenLock = new();
		private static string _cachedToken;
		private static string _cachedTokenFingerprint;
		private static DateTimeOffset _tokenIssuedAt;
		private static readonly TimeSpan TokenLifetime = TimeSpan.FromMinutes(50);

		/// <summary>Sends one push to one device.</summary>
		public async Task<PushSendOutcome> Send(FcmSettings settings, DeviceInfo device, PushMessage message)
		{
			string accessToken;
			try
			{
				accessToken = await GetAccessToken(settings);
			}
			catch (Exception ex)
			{
				return new PushSendOutcome { ok = false, reason = $"failed to get FCM access token: {ex.Message}" };
			}

			var payload = BuildPayload(device.token, message);

			using var request = new HttpRequestMessage(HttpMethod.Post, settings.SendUrl)
			{
				Content = new StringContent(payload, Encoding.UTF8, "application/json"),
			};
			request.Headers.TryAddWithoutValidation("authorization", $"Bearer {accessToken}");

			try
			{
				using var response = await Http.SendAsync(request);
				if (response.StatusCode == HttpStatusCode.OK)
					return new PushSendOutcome { ok = true };

				var bodyText = await response.Content.ReadAsStringAsync();
				var reason = ExtractError(bodyText) ?? response.StatusCode.ToString();
				// FCM marks a token dead with these codes (404 UNREGISTERED, 400 INVALID_ARGUMENT).
				var dead = reason is "UNREGISTERED" or "INVALID_ARGUMENT"
					|| response.StatusCode == HttpStatusCode.NotFound;

				BeamableLogger.LogWarning("FCM rejected push ({status}): {reason}", (int)response.StatusCode, reason);
				return new PushSendOutcome { ok = false, reason = reason, tokenIsInvalid = dead };
			}
			catch (Exception ex)
			{
				return new PushSendOutcome { ok = false, reason = $"transport error: {ex.Message}" };
			}
		}

		/// <summary>
		/// Builds the FCM HTTP v1 message as a DATA-ONLY, high-priority message (no
		/// <c>notification</c> block).
		///
		/// Why data-only: a message WITH a <c>notification</c> block is displayed by the OS
		/// directly and does NOT invoke <c>FirebaseMessagingService.onMessageReceived</c> when
		/// the app is backgrounded/killed — so the Beamable receive-time handler
		/// (PushNotificationReceivedHandler) never runs in that state. A data-only message DOES
		/// invoke <c>onMessageReceived</c> in every state (foreground, background, killed), so the
		/// handler fires; the Beamable library then builds the tray notification itself
		/// (PushFirebaseService.displayDataMessage). Keys must match what the library reads:
		/// <c>title</c>, <c>body</c>, <c>deeplink</c> (lowercase). FCM data values must be strings.
		/// </summary>
		private static string BuildPayload(string deviceToken, PushMessage message)
		{
			var data = new Dictionary<string, object>();
			if (!string.IsNullOrWhiteSpace(message.title)) data["title"] = message.title;
			if (!string.IsNullOrWhiteSpace(message.body)) data["body"] = message.body;
			if (!string.IsNullOrWhiteSpace(message.deepLink)) data["deeplink"] = message.deepLink;

			var msg = new Dictionary<string, object>
			{
				["token"] = deviceToken,
				["data"] = data,
				["android"] = new Dictionary<string, object> { ["priority"] = "high" },
			};

			var root = new Dictionary<string, object> { ["message"] = msg };
			return JsonSerializer.Serialize(root);
		}

		// --- OAuth2 access token --------------------------------------------

		private static async Task<string> GetAccessToken(FcmSettings settings)
		{
			lock (TokenLock)
			{
				var fresh = _cachedToken != null
					&& _cachedTokenFingerprint == settings.ClientEmail
					&& DateTimeOffset.UtcNow - _tokenIssuedAt < TokenLifetime;
				if (fresh) return _cachedToken;
			}

			var token = await RequestAccessToken(settings);

			lock (TokenLock)
			{
				_cachedToken = token;
				_cachedTokenFingerprint = settings.ClientEmail;
				_tokenIssuedAt = DateTimeOffset.UtcNow;
				return _cachedToken;
			}
		}

		/// <summary>Mints a JWT assertion and exchanges it for an OAuth2 access token.</summary>
		private static async Task<string> RequestAccessToken(FcmSettings settings)
		{
			var assertion = SignAssertion(settings);

			using var request = new HttpRequestMessage(HttpMethod.Post, settings.TokenUri)
			{
				Content = new FormUrlEncodedContent(new Dictionary<string, string>
				{
					["grant_type"] = "urn:ietf:params:oauth:grant-type:jwt-bearer",
					["assertion"] = assertion,
				}),
			};

			using var response = await Http.SendAsync(request);
			var body = await response.Content.ReadAsStringAsync();
			if (!response.IsSuccessStatusCode)
				throw new Exception($"token endpoint returned {(int)response.StatusCode}: {body}");

			using var doc = JsonDocument.Parse(body);
			if (doc.RootElement.TryGetProperty("access_token", out var token) && token.ValueKind == JsonValueKind.String)
				return token.GetString();

			throw new Exception($"token endpoint response had no access_token: {body}");
		}

		/// <summary>
		/// Imports the service-account RSA key to confirm it's well-formed. The #1 risk when
		/// pasting the service-account JSON into Realm Config is the <c>private_key</c> losing
		/// its newlines — this throws a clear message in that case. Used by the admin
		/// <c>CheckFcmConfig</c> diagnostic; does no network I/O.
		/// </summary>
		public static void EnsureKeyLoads(FcmSettings settings)
		{
			try
			{
				using var rsa = RSA.Create();
				rsa.ImportFromPem(settings.PrivateKeyPem);
			}
			catch (Exception ex)
			{
				throw new Exception(
					$"private_key could not be parsed as a PEM RSA key — check that the pasted JSON kept its newlines: {ex.Message}");
			}
		}

		/// <summary>Builds and RS256-signs the JWT bearer assertion for the token exchange.</summary>
		private static string SignAssertion(FcmSettings settings)
		{
			var header = "{\"alg\":\"RS256\",\"typ\":\"JWT\"}";
			var iat = DateTimeOffset.UtcNow.ToUnixTimeSeconds();
			var exp = iat + 3600;
			var claims =
				$"{{\"iss\":\"{settings.ClientEmail}\",\"scope\":\"{FcmSettings.MessagingScope}\"," +
				$"\"aud\":\"{settings.TokenUri}\",\"iat\":{iat},\"exp\":{exp}}}";

			var signingInput = $"{Base64Url(Encoding.UTF8.GetBytes(header))}.{Base64Url(Encoding.UTF8.GetBytes(claims))}";

			using var rsa = RSA.Create();
			rsa.ImportFromPem(settings.PrivateKeyPem);
			var signature = rsa.SignData(
				Encoding.UTF8.GetBytes(signingInput),
				HashAlgorithmName.SHA256,
				RSASignaturePadding.Pkcs1);

			return $"{signingInput}.{Base64Url(signature)}";
		}

		private static string Base64Url(byte[] bytes) =>
			Convert.ToBase64String(bytes).TrimEnd('=').Replace('+', '-').Replace('/', '_');

		/// <summary>
		/// Pulls the FCM error code out of an HTTP v1 error body. Prefers the
		/// FCM-specific <c>error.details[].errorCode</c>, falling back to <c>error.status</c>.
		/// </summary>
		private static string ExtractError(string errorBody)
		{
			if (string.IsNullOrWhiteSpace(errorBody)) return null;
			try
			{
				using var doc = JsonDocument.Parse(errorBody);
				if (!doc.RootElement.TryGetProperty("error", out var error)) return null;

				if (error.TryGetProperty("details", out var details) && details.ValueKind == JsonValueKind.Array)
				{
					foreach (var detail in details.EnumerateArray())
					{
						if (detail.TryGetProperty("errorCode", out var code) && code.ValueKind == JsonValueKind.String)
							return code.GetString();
					}
				}

				return error.TryGetProperty("status", out var status) ? status.GetString() : null;
			}
			catch
			{
				return null;
			}
		}
	}
}
