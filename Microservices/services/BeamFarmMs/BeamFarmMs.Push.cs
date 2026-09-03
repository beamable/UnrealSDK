using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Common.Api.Stats;
using Beamable.Server;

namespace Beamable.BeamFarmMs
{
	/// <summary>
	/// Device-token registration for remote push (APNs on iOS, FCM on Android).
	///
	/// The OS hands the app a device token (iOS via the BeamableNotifications SDK's
	/// <c>OnTokenReceived</c> event); the app forwards it here via <see cref="RegisterDeviceToken"/>.
	/// Tokens are stored as a <b>private</b> per-player stat holding a JSON array (one token per
	/// device) — Stats is built into every realm, so there is no MongoDB to provision and a player
	/// only ever has a handful of devices. A separate <b>public</b> marker stat keeps the device
	/// <i>count</i> so an admin/back-office tool could later enumerate registered players.
	///
	/// Modeled on the ReactNative PushNotificationService sample (registration half only). The
	/// matching "send" half (APNs/FCM clients) is intentionally out of scope here.
	/// </summary>
	public partial class BeamFarmMs : Microservice
	{
		/// <summary>Private per-player stat holding the JSON device-token list.</summary>
		private const string DeviceStatKey = "apns_devices";

		/// <summary>Public, searchable companion stat holding the player's registered device count.</summary>
		private const string PublicMarkerStatKey = "push_devices";

		private static readonly JsonSerializerOptions PushJsonOptions = new()
		{
			IncludeFields = true, // DeviceInfo uses public fields, not properties
		};

		/// <summary>
		/// Registers (or refreshes) the calling player's device token. Safe to call repeatedly —
		/// the same token is de-duplicated and its timestamp refreshed.
		/// </summary>
		/// <param name="token">The device token from the OS (APNs hex token, or FCM registration token).</param>
		/// <param name="environment">APNs only: "sandbox" (dev/TestFlight) or "production" (App Store). Empty → realm default. Ignored for FCM.</param>
		/// <param name="platform">"apns" (default, iOS) or "fcm" (Android). Empty → "apns".</param>
		[ClientCallable]
		public async Task<RegisterResult> RegisterDeviceToken(string token, string environment, string platform)
		{
			if (string.IsNullOrWhiteSpace(token))
				return new RegisterResult { success = false, message = "A non-empty device token is required.", deviceCount = 0 };

			var plat = NormalizePlatform(platform);
			var env = NormalizeEnvironment(environment);
			var devices = await LoadDevices(Context.UserId);

			var existing = devices.FirstOrDefault(d => d.token == token);
			if (existing != null)
			{
				existing.platform = plat;
				existing.environment = env;
				existing.updatedAt = DateTimeOffset.UtcNow.ToUnixTimeSeconds();
			}
			else
			{
				devices.Add(new DeviceInfo
				{
					token = token,
					platform = plat,
					environment = env,
					updatedAt = DateTimeOffset.UtcNow.ToUnixTimeSeconds(),
				});
			}

			await SaveDevices(Context.UserId, devices);
			BeamableLogger.Log("Registered push device for player {player} ({count} total)", Context.UserId, devices.Count);
			return new RegisterResult { success = true, deviceCount = devices.Count, message = "Device registered." };
		}

		/// <summary>Removes one of the calling player's device tokens (e.g. on logout).</summary>
		[ClientCallable]
		public async Task<UnregisterResult> UnregisterDeviceToken(string token)
		{
			var devices = await LoadDevices(Context.UserId);
			var removed = devices.RemoveAll(d => d.token == token);
			await SaveDevices(Context.UserId, devices);
			return new UnregisterResult
			{
				success = removed > 0,
				deviceCount = devices.Count,
				message = removed > 0 ? "Device removed." : "Token was not registered.",
			};
		}

		// --- Persistence ----------------------------------------------------

		/// <summary>Loads the device list for a player (empty list if none registered).</summary>
		private async Task<List<DeviceInfo>> LoadDevices(long playerId)
		{
			var raw = await Services.Stats.GetStat(
				StatsDomainType.Game, StatsAccessType.Private, playerId, DeviceStatKey);

			if (string.IsNullOrWhiteSpace(raw)) return new List<DeviceInfo>();

			try
			{
				return JsonSerializer.Deserialize<List<DeviceInfo>>(raw, PushJsonOptions) ?? new List<DeviceInfo>();
			}
			catch (Exception ex)
			{
				BeamableLogger.LogError("Failed to parse stored devices for {player}: {msg}", playerId, ex.Message);
				return new List<DeviceInfo>();
			}
		}

		/// <summary>
		/// Persists the device list for a player and refreshes the public searchable marker with the
		/// new device count. Single choke point for every mutation, so the marker stays in sync.
		/// </summary>
		private async Task SaveDevices(long playerId, List<DeviceInfo> devices)
		{
			var json = JsonSerializer.Serialize(devices, PushJsonOptions);
			await Services.Stats.SetStat(
				StatsDomainType.Game, StatsAccessType.Private, playerId, DeviceStatKey, json);

			await Services.Stats.SetStat(
				StatsDomainType.Game, StatsAccessType.Public, playerId, PublicMarkerStatKey, devices.Count.ToString());
		}

		// --- Helpers --------------------------------------------------------

		/// <summary>Normalizes a platform tag; null/empty/unknown defaults to APNs.</summary>
		private static string NormalizePlatform(string platform)
		{
			if (string.IsNullOrWhiteSpace(platform)) return PushPlatform.Apns;
			var p = platform.Trim().ToLowerInvariant();
			return p is "fcm" or "android" or "firebase" ? PushPlatform.Fcm : PushPlatform.Apns;
		}

		/// <summary>Normalizes an APNs environment; null/empty → null (resolved against the realm default at send time).</summary>
		private static string NormalizeEnvironment(string environment)
		{
			if (string.IsNullOrWhiteSpace(environment)) return null;
			var e = environment.Trim().ToLowerInvariant();
			return e is "sandbox" or "dev" or "development" ? "sandbox" : "production";
		}
	}

	/// <summary>Which push provider a device's token belongs to.</summary>
	public static class PushPlatform
	{
		public const string Apns = "apns"; // iOS
		public const string Fcm = "fcm";   // Android (and any FCM client)
	}

	/// <summary>A registered device.</summary>
	[Serializable]
	public class DeviceInfo
	{
		public string token;
		public string platform;    // "apns" (default, iOS) or "fcm" (Android).
		public string environment; // APNs only: "sandbox" / "production" / null.
		public long updatedAt;     // unix seconds.
	}

	/// <summary>Result of registering a device token.</summary>
	[Serializable]
	public class RegisterResult
	{
		public bool success;
		public int deviceCount;
		public string message;
	}

	/// <summary>
	/// Result of unregistering a device. A distinct type from <see cref="RegisterResult"/> so the
	/// generated client emits one return type per endpoint (avoids a duplicate declaration).
	/// </summary>
	[Serializable]
	public class UnregisterResult
	{
		public bool success;
		public int deviceCount;
		public string message;
	}
}
