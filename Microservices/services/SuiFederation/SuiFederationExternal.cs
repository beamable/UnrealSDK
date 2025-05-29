using Beamable.Common;
using Beamable.SuiFederation.Endpoints;
using SuiFederationCommon;

namespace Beamable.SuiFederation;

public partial class SuiFederation : IFederatedLogin<SuiWeb3ExternalIdentity>
{
    async Promise<FederatedAuthenticationResponse> IFederatedLogin<SuiWeb3ExternalIdentity>.Authenticate(string token, string challenge, string solution)
    {
        return await Provider.GetService<AuthenticateExternalEndpoint>()
            .Authenticate(token, challenge, solution);
    }
}