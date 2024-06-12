using System;
using System.Net;
using System.Net.Http;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Server;
using Beamable.Server.Api.RealmConfig;
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
			BeamableLogger.Log("Authenticate");
			var uri = BuildAuthenticateUri(token);
			var response = await _client.SendAsync(new HttpRequestMessage(HttpMethod.Get, uri));
			Debug.Log($"RESPONSE: {response.RequestMessage}");
			response.EnsureSuccessStatusCode();
			return new FederatedAuthenticationResponse { user_id = Context.UserId.ToString() };
		}

		private string BuildAuthenticateUri(string ticket)
		{
			return $"{AuthenticateUserTicketUri}/?key={_publisherToken}&appid={_appId}&ticket={ticket}";
		}
	}

    public class SteamIdentity : IThirdPartyCloudIdentity
    {
        public string UniqueName => "steam_federated";
    }

}
