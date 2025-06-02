using System.Collections.Generic;
using System.Linq;
using Beamable.Common;
using Beamable.Common.Api.Inventory;
using Beamable.Server;
using Beamable.SuiFederation.Features.ChannelProcessor;
using Beamable.SuiFederation.Features.Content.Models;
using Beamable.SuiFederation.Features.Inventory;
using Beamable.SuiFederation.Features.Inventory.Models;
using Beamable.SuiFederation.Features.Notifications.Models;
using Beamable.SuiFederation.Features.Transactions;

namespace Beamable.SuiFederation.Endpoints;

public class StartInventoryTransactionEndpoint : IEndpoint
{
    private readonly TransactionManager _transactionManager;
    private readonly InventoryService _inventoryService;
    private readonly RequestContext _requestContext;
    private readonly UpdatePlayerStateService _updatePlayerStateService;

    public StartInventoryTransactionEndpoint(TransactionManager transactionManager, InventoryService inventoryService, RequestContext requestContext, UpdatePlayerStateService updatePlayerStateService)
    {
        _transactionManager = transactionManager;
        _inventoryService = inventoryService;
        _requestContext = requestContext;
        _updatePlayerStateService = updatePlayerStateService;
    }

    public async Promise<FederatedInventoryProxyState> StartInventoryTransaction(string id, string transaction, Dictionary<string, long> currencies, List<FederatedItemCreateRequest> newItems, List<FederatedItemDeleteRequest> deleteItems, List<FederatedItemUpdateRequest> updateItems, UserRequestDataHandler user)
    {
        var transactionId = await _transactionManager.StartTransaction(id, nameof(StartInventoryTransaction), transaction, currencies, newItems, deleteItems, updateItems);
        _transactionManager.SetCurrentTransactionContext(transactionId);
        _ = _transactionManager.RunAsyncBlock(transactionId, transaction, async () =>
        {
            // NEW ITEMS
            var currencyRequest = currencies.Select(c => new InventoryRequest(_requestContext.UserId, c.Key, c.Value, new Dictionary<string, string>()));
            var itemsRequest = newItems.Select(i => new InventoryRequest(_requestContext.UserId, i.contentId, 1, i.properties));
            await ChannelService.Enqueue(user, async (_) =>
                await _inventoryService.NewItems(transactionId.ToString(), id, currencyRequest.Union(itemsRequest), user)
            );

            // UPDATE ITEMS
            var updateItemsRequest = updateItems.Select(i => new InventoryRequestUpdate(_requestContext.UserId,
                i.contentId, i.proxyId,
                i.properties
                    .Where(kvp => !NftContentItemExtensions.FixedProperties().Contains(kvp.Key))
                    .ToDictionary(kvp => kvp.Key, kvp => kvp.Value)));
            await ChannelService.Enqueue(user, async (_) =>
                await _inventoryService.UpdateItems(transactionId.ToString(), id, updateItemsRequest, user)
            );

            // DELETE ITEMS
            var deleteItemsRequest = deleteItems.Select(i => new InventoryRequestDelete(_requestContext.UserId,
                i.contentId, i.proxyId));
            await ChannelService.Enqueue(user, async (_) =>
                await _inventoryService.DeleteItems(transactionId.ToString(), id, deleteItemsRequest, user)
            );

            await ChannelService.Enqueue(user, async (_) =>
                await _updatePlayerStateService.Update(new InventoryTransactionNotification
                {
                    InventoryTransactionId = transaction
                }, user)
            );
            BeamableLogger.Log("ChannelService queue lenght {GetQueueLength}", ChannelService.GetQueueLength());
        });

        return await _inventoryService.GetLastKnownState(id);
    }
}