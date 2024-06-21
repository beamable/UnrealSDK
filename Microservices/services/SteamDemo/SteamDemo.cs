using System;
using System.Net;
using System.Net.Http;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Server;
using Beamable.Server.Api.RealmConfig;
using Newtonsoft.Json;
using UnityEngine;

namespace Beamable.SteamDemo
{
	[Microservice("SteamDemo")]
	public class SteamDemo : Microservice, IFederatedLogin<SteamIdentity>
	{
		private const string BaseUri = "https://partner.steam-api.com";
		private const string AuthenticateUserTicketUri = BaseUri + "/ISteamUserAuth/AuthenticateUserTicket/v1";

		private readonly HttpClient _client = new HttpClient();
		private static string _appId;
		private static string _publisherToken;

		[InitializeServices]
		public static async Task Initialize(IServiceInitializer initializer)
		{
			try
			{
				var realmConfigService = initializer.GetService<IMicroserviceRealmConfigService>();
				var config = await realmConfigService.GetRealmConfigSettings();
				_appId = config.GetSetting("steam", "appid", string.Empty);
				if (string.IsNullOrWhiteSpace(_appId))
				{
					throw new MicroserviceException((int)HttpStatusCode.BadRequest, "ConfigurationError",
						"steam.appid is not defined in realm config. Please apply the configuration and restart the service to make it operational.");
				}
				_publisherToken = config.GetSetting("steam", "key", string.Empty);
				if (string.IsNullOrWhiteSpace(_publisherToken))
				{
					throw new MicroserviceException((int)HttpStatusCode.BadRequest, "ConfigurationError",
						"steam.key is not defined in realm config. Please apply the configuration and restart the service to make it operational.");
				}
			}
			catch (Exception ex)
			{
				BeamableLogger.LogException(ex);
				BeamableLogger.LogError("Service initialization failed. Please fix the issues before using the service.");
			}
		}

		public async Promise<FederatedAuthenticationResponse> Authenticate(string token, string challenge,
			string solution)
		{
			BeamableLogger.Log("Request for authentication started");
			_publisherToken = (await Services.RealmConfig.GetRealmConfigSettings()).GetSetting("steam", "key");
			var uri = BuildAuthenticateUri(token);
			var response = await _client.SendAsync(new HttpRequestMessage(HttpMethod.Get, uri));
			if (response.IsSuccessStatusCode)
			{
				var responseBody = await response.Content.ReadAsStringAsync();
				try
				{
					var ticket = JsonConvert.DeserializeObject<SteamAuthenticateUserTicket>(responseBody);
					return new FederatedAuthenticationResponse { user_id = ticket.response.ResponseParams.steamid };
				}
				catch (Exception)
				{
					throw new MicroserviceException(500, "AuthenticationError",
						"Failed to deserialize response from Steam.");
				}
			}
			Debug.Log($"Failed request, {response.StatusCode}: {response.RequestMessage}");

			throw new MicroserviceException((int)response.StatusCode, "AuthenticationError",
				$"Failed to connect to Steam: {response.ReasonPhrase}");
		}

		private string BuildAuthenticateUri(string ticket)
		{
			return $"{AuthenticateUserTicketUri}/?key={_publisherToken}&appid={_appId}&ticket={ticket}";
		}
	}

	public class SteamIdentity : IThirdPartyCloudIdentity
	{
		public string UniqueName => "federated_steam";
	}

	[Serializable]
	public class SteamAuthenticateUserTicket
	{
		public SteamResponse response { get; set; }
	}

	[Serializable]
	public class SteamResponse
	{
		[JsonProperty(PropertyName = "params")]
		public SteamResponseParams ResponseParams { get; set; }
	}

	[Serializable]
	public class SteamResponseParams
	{
		public string result { get; set; }
		public string steamid { get; set; }
		public string ownersteamid { get; set; }
		public bool vacbanned { get; set; }
		public bool publisherbanned { get; set; }
	}

}
