using System.Collections.Generic;
using Beamable.Common;
using Beamable.Common.Api.Inventory;
using Beamable.SuiFederation.Endpoints;
using Beamable.SuiFederation.Extensions;
using Beamable.SuiFederation.Features.Accounts;
using SuiFederationCommon;

namespace Beamable.SuiFederation;

public partial class SuiFederation : IFederatedInventory<SuiWeb3ExternalIdentity>
{
    async Promise<FederatedAuthenticationResponse> IFederatedLogin<SuiWeb3ExternalIdentity>.Authenticate(string token, string challenge, string solution)
    {
        return await Provider.GetService<AuthenticateExternalEndpoint>()
            .Authenticate(token, challenge, solution);
    }

    async Promise<FederatedInventoryProxyState> IFederatedInventory<SuiWeb3ExternalIdentity>.GetInventoryState(string id)
    {
        var microserviceInfo = MicroserviceMetadataExtensions.GetMetadata<SuiFederation, SuiWeb3ExternalIdentity>();
        var existingExternalIdentity = microserviceInfo.ToExternalIdentity();
        return await Provider.GetService<GetInventoryStateEndpoint>()
            .GetInventoryState(id, existingExternalIdentity);
    }

    async Promise<FederatedInventoryProxyState> IFederatedInventory<SuiWeb3ExternalIdentity>.StartInventoryTransaction(string id, string transaction, Dictionary<string, long> currencies, List<FederatedItemCreateRequest> newItems, List<FederatedItemDeleteRequest> deleteItems,
        List<FederatedItemUpdateRequest> updateItems)
    {
        var gamerTag = await Provider.GetService<AccountsService>().GetGamerTag(id);
        var microserviceInfo = MicroserviceMetadataExtensions.GetMetadata<SuiFederation, SuiWeb3ExternalIdentity>();
        return await Provider.GetService<StartInventoryTransactionExternalEndpoint>()
            .StartInventoryTransaction(id, transaction, currencies, newItems, deleteItems, updateItems, gamerTag, microserviceInfo);
    }
}