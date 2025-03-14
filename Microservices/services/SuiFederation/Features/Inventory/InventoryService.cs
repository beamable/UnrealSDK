using System.Collections.Generic;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Server.Content;
using Beamable.SuiFederation.Extensions;
using Beamable.SuiFederation.Features.Content;
using Beamable.SuiFederation.Features.Inventory.Models;
using Beamable.SuiFederation.Features.Inventory.Storage;

namespace Beamable.SuiFederation.Features.Inventory;

public class InventoryService(
    ContentHandlerFactory contentHandlerFactory,
    InventoryStateCollection inventoryStateCollection,
    ContentService contentService) : IService
{
    public async Task NewItems(string transaction, string id, IEnumerable<InventoryRequest> mintRequests)
    {
        var messageRequests = await mintRequests.GroupByAsync(
            async request =>
            {
                var contentObject = await contentService.GetContent(request.ContentId);
                var handler = contentHandlerFactory.GetHandler(contentObject);
                return await handler.ConstructMessage(transaction, id, request, contentObject);
            },
            message => message.GetType()
        );

        foreach (var request in messageRequests)
        {
            var handler = contentHandlerFactory.GetHandler(request.Key);
            await handler.SendMessages(transaction, request.Value);
        }
    }

    public async Task UpdateItems(string transaction, string id, IEnumerable<InventoryRequestUpdate> updateItemsRequest)
    {
        var messageRequests = await updateItemsRequest.GroupByAsync(
            async request =>
            {
                var contentObject = await contentService.GetContent(request.ContentId);
                var handler = contentHandlerFactory.GetHandler(contentObject);
                return await handler.ConstructMessage(transaction, id, request, contentObject);
            },
            message => message.GetType()
        );

        foreach (var request in messageRequests)
        {
            var handler = contentHandlerFactory.GetHandler(request.Key);
            await handler.SendMessages(transaction, request.Value);
        }
    }

    public async Task<FederatedInventoryProxyState> GetLastKnownState(string id)
    {
        var lastKnownState = await inventoryStateCollection.Get(id.ToLower());
        return lastKnownState ?? new FederatedInventoryProxyState
        {
            currencies = new Dictionary<string, long>(),
            items = new Dictionary<string, List<FederatedItemProxy>>()
        };
    }
}