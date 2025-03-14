using System.Collections.Generic;
using System.Linq;
using Beamable.Common;
using Beamable.Common.Api.Inventory;
using Beamable.Server;
using Beamable.SuiFederation.Features.Content.Models;
using Beamable.SuiFederation.Features.Inventory;
using Beamable.SuiFederation.Features.Inventory.Models;
using Beamable.SuiFederation.Features.Notifications.Models;
using Beamable.SuiFederation.Features.Transactions;

namespace Beamable.SuiFederation.Endpoints;

public class StartInventoryTransactionEndpoint(
    TransactionManager transactionManager,
    InventoryService inventoryService,
    RequestContext requestContext,
    UpdatePlayerStateService updatePlayerStateService) : IEndpoint
{
    public async Promise<FederatedInventoryProxyState> StartInventoryTransaction(string id, string transaction, Dictionary<string, long> currencies, List<FederatedItemCreateRequest> newItems, List<FederatedItemDeleteRequest> deleteItems, List<FederatedItemUpdateRequest> updateItems)
    {
        var transactionId = await transactionManager.StartTransaction(id, nameof(StartInventoryTransaction), transaction, currencies, newItems, deleteItems, updateItems);
        transactionManager.SetCurrentTransactionContext(transactionId);
        _ = transactionManager.RunAsyncBlock(transactionId, transaction, async () =>
        {
            // NEW ITEMS
            var currencyRequest = currencies.Select(c => new InventoryRequest(requestContext.UserId, c.Key, c.Value, new Dictionary<string, string>()));
            var itemsRequest = newItems.Select(i => new InventoryRequest(requestContext.UserId, i.contentId, 1, i.properties));
            await inventoryService.NewItems(transactionId.ToString(), id, currencyRequest.Union(itemsRequest));

            // UPDATE ITEMS
            var updateItemsRequest = updateItems.Select(i => new InventoryRequestUpdate(requestContext.UserId,
                i.contentId, i.proxyId,
                i.properties
                    .Where(kvp => !NftContentItemExtensions.FixedProperties().Contains(kvp.Key))
                    .ToDictionary(kvp => kvp.Key, kvp => kvp.Value)));
            await inventoryService.UpdateItems(transactionId.ToString(), id, updateItemsRequest);

            await updatePlayerStateService.Update(new InventoryTransactionNotification
            {
                InventoryTransactionId = transaction
            });
        });

        return await inventoryService.GetLastKnownState(id);
    }
}