using System;
using Beamable.Common;
using Beamable.Server;
using Beamable.SuiFederation.Extensions;
using Beamable.SuiFederation.Features.Accounts;
using Beamable.SuiFederation.Features.Accounts.Exceptions;
using SuiFederationCommon;

namespace Beamable.SuiFederation.Endpoints;

public class AuthenticateEndpoint : IEndpoint
{
    private readonly AccountsService _accountsService;
    private readonly Configuration _configuration;
    private readonly RequestContext _requestContext;

    public AuthenticateEndpoint(AccountsService accountsService, Configuration configuration, RequestContext requestContext)
    {
        _accountsService = accountsService;
        _configuration = configuration;
        _requestContext = requestContext;
    }

    public async Promise<FederatedAuthenticationResponse> Authenticate(string token, string challenge, string solution)
    {
        // Check if an external identity is already attached (from request context)
        if (_requestContext.UserId != 0L)
        {
            var microserviceInfo = MicroserviceMetadataExtensions.GetMetadata<SuiFederation, SuiWeb3Identity>();
            var existingExternalIdentity = _requestContext.GetExternalIdentity(microserviceInfo);

            if (existingExternalIdentity is not null)
            {
                return new FederatedAuthenticationResponse
                {
                    user_id = existingExternalIdentity.userId
                };
            }
        }

        if (string.IsNullOrEmpty(token) && _requestContext.UserId != 0L)
        {
            // Create new account for player if token is empty
            var account = await _accountsService.GetOrCreateAccount(_requestContext.UserId.ToString());
            return new FederatedAuthenticationResponse
            {
                user_id = account.Address
            };
        }

        throw new UnauthorizedException($"{SuiFederationSettings.SuiIdentityName} namespace is not used for external wallets.");
    }
}