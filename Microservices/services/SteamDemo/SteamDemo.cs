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
    [FederationId("steam")]
    public class SteamId : IFederationId;
    
    [Microservice("SteamDemo")]
    public partial class SteamDemo : Microservice, IFederatedLogin<SteamId>
    {
        private const string BaseUri = "https://partner.steam-api.com";
        private const string AuthenticateUserTicketUri = BaseUri + "/ISteamUserAuth/AuthenticateUserTicket/v1";

        [InitializeServices]
        public static async Task Initialize(IServiceInitializer initializer)
        {
            try
            {
                var realmConfigService = initializer.GetService<IMicroserviceRealmConfigService>();
                var config = await realmConfigService.GetRealmConfigSettings();
                var appId = config.GetSetting("steam", "appid", string.Empty);
                if (string.IsNullOrWhiteSpace(appId))
                {
                    throw new MicroserviceException((int)HttpStatusCode.BadRequest, "ConfigurationError",
                        "steam.appid is not defined in realm config. Please apply the configuration and restart the service to make it operational.");
                }

                var publisherToken = config.GetSetting("steam", "key", string.Empty);
                if (string.IsNullOrWhiteSpace(publisherToken))
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

        public async Promise<FederatedAuthenticationResponse> Authenticate(string token, string challenge, string solution)
        {
            BeamableLogger.Log("Request for authentication started");
            var realmSettings = await Services.RealmConfig.GetRealmConfigSettings();
            
            var publisherToken = realmSettings.GetSetting("steam", "key");
            var appId = realmSettings.GetSetting("steam", "appid");
            
            var uri = BuildAuthenticateUri(token, publisherToken, appId);

            var client = new HttpClient();
            var response = await client.SendAsync(new HttpRequestMessage(HttpMethod.Get, uri));
            if (response.IsSuccessStatusCode)
            {
                var responseBody = await response.Content.ReadAsStringAsync();
                try
                {
                    var ticket = JsonConvert.DeserializeObject<SteamAuthenticateUserTicket>(responseBody);
                    return new FederatedAuthenticationResponse { user_id = ticket.response.ResponseParams.steamid, };
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

        private static string BuildAuthenticateUri(string ticket, string publisherToken, string appId)
        {
            return $"{AuthenticateUserTicketUri}/?key={publisherToken}&appid={appId}&ticket={ticket}";
        }
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