using System.Collections.Generic;
using System.Linq;
using Beamable.Common;
using Beamable.Common.Api.Inventory;
using Beamable.SuiFederation.Extensions;
using Beamable.SuiFederation.Features.ChannelProcessor;
using Beamable.SuiFederation.Features.Content.Models;
using Beamable.SuiFederation.Features.Inventory;
using Beamable.SuiFederation.Features.Inventory.Models;
using Beamable.SuiFederation.Features.Notifications.Models;
using Beamable.SuiFederation.Features.Transactions;

namespace Beamable.SuiFederation.Endpoints;

public class StartInventoryTransactionExternalEndpoint : IEndpoint
{
    private readonly TransactionManager _transactionManager;
    private readonly InventoryService _inventoryService;
    private readonly UpdatePlayerStateService _updatePlayerStateService;
    private readonly GetInventoryStateEndpoint _inventoryStateEndpoint;

    public StartInventoryTransactionExternalEndpoint(TransactionManager transactionManager, InventoryService inventoryService, UpdatePlayerStateService updatePlayerStateService, GetInventoryStateEndpoint inventoryStateEndpoint)
    {
        _transactionManager = transactionManager;
        _inventoryService = inventoryService;
        _updatePlayerStateService = updatePlayerStateService;
        _inventoryStateEndpoint = inventoryStateEndpoint;
    }

    public async Promise<FederatedInventoryProxyState> StartInventoryTransaction(string id, string transaction, Dictionary<string, long> currencies, List<FederatedItemCreateRequest> newItems, List<FederatedItemDeleteRequest> deleteItems, List<FederatedItemUpdateRequest> updateItems, long gamerTag, MicroserviceInfo microserviceInfo)
    {
        var transactionId = await _transactionManager.StartTransaction(id, nameof(StartInventoryTransaction), transaction, currencies, newItems, deleteItems, updateItems);
        _transactionManager.SetCurrentTransactionContext(transactionId);
        _ = _transactionManager.RunAsyncBlock(transactionId, transaction, async () =>
        {
            // NEW ITEMS
            var currencyRequest = currencies.Select(c => new InventoryRequest(gamerTag, c.Key, c.Value, new Dictionary<string, string>()));
            var itemsRequest = newItems.Select(i => new InventoryRequest(gamerTag, i.contentId, 1, i.properties));
            await ChannelService.Enqueue(gamerTag, async (_) =>
                await _inventoryService.NewItems(transactionId.ToString(), id, currencyRequest.Union(itemsRequest), gamerTag)
            );

            await ChannelService.Enqueue(gamerTag, async (_) =>
                await _updatePlayerStateService.Update(new InventoryTransactionNotification
                {
                    InventoryTransactionId = transaction
                }, _inventoryStateEndpoint, microserviceInfo)
            );
            BeamableLogger.Log("ChannelService queue lenght {GetQueueLength}", ChannelService.GetQueueLength());
        });

        return await _inventoryService.GetLastKnownState(id);
    }
}