using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Server;

namespace Beamable.SteamDemo
{
	[Microservice("SteamDemo")]
	public class SteamDemo : Microservice, IFederatedLogin<SteamIdentity>
	{
		public async Promise<FederatedAuthenticationResponse> Authenticate(string token, string challenge,
			string solution)
		{
			BeamableLogger.Log("Authenticate");
			await Task.Delay(1);
			return new FederatedAuthenticationResponse { user_id = Context.UserId.ToString() };
		}
	}

    public class SteamIdentity : IThirdPartyCloudIdentity
    {
        public string UniqueName => "steam_federated";
    }

}
