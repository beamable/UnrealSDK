using System.Net.Http;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Server;
using UnityEngine;

namespace Beamable.SteamDemo
{
	[Microservice("SteamDemo")]
	public class SteamDemo : Microservice, IFederatedLogin<SteamIdentity>
	{
		private const string BaseUri = "https://partner.steam-api.com";
		private const string AuthenticateUserTicketUri = BaseUri + "/ISteamUserAuth/AuthenticateUserTicket/v1";
		
		private readonly HttpClient _client = new HttpClient();
		public async Promise<FederatedAuthenticationResponse> Authenticate(string token, string challenge,
			string solution)
		{
			BeamableLogger.Log("Authenticate");
			var uri = await BuildAuthenticateUri(token);
			var response = await _client.SendAsync(new HttpRequestMessage(HttpMethod.Get, uri));
			Debug.Log($"RESPONSE: {response.RequestMessage}");
			response.EnsureSuccessStatusCode();
			return new FederatedAuthenticationResponse { user_id = Context.UserId.ToString() };
		}

		private async Task<string> BuildAuthenticateUri(string ticket)
		{
			var realmConfigSettings = await this.Services.RealmConfig.GetRealmConfigSettings();
			var appId = realmConfigSettings.GetSetting("steam", "appId", "480");
			var publisherToken = realmConfigSettings.GetSetting("steam", "publisherToken", "NONE");
			return $"{AuthenticateUserTicketUri}/?key={publisherToken}&appid={appId}&ticket={ticket}";
		}
	}

    public class SteamIdentity : IThirdPartyCloudIdentity
    {
        public string UniqueName => "steam_federated";
    }

}
