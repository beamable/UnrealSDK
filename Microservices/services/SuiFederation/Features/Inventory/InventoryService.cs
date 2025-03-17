using System.Collections.Generic;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Server.Content;
using Beamable.SuiFederation.Extensions;
using Beamable.SuiFederation.Features.Content;
using Beamable.SuiFederation.Features.Inventory.Models;
using Beamable.SuiFederation.Features.Inventory.Storage;

namespace Beamable.SuiFederation.Features.Inventory;

public class InventoryService : IService
{
    private readonly ContentHandlerFactory _contentHandlerFactory;
    private readonly InventoryStateCollection _inventoryStateCollection;
    private readonly ContentService _contentService;

    public InventoryService(ContentHandlerFactory contentHandlerFactory, InventoryStateCollection inventoryStateCollection, ContentService contentService)
    {
        _contentHandlerFactory = contentHandlerFactory;
        _inventoryStateCollection = inventoryStateCollection;
        _contentService = contentService;
    }

    public async Task NewItems(string transaction, string id, IEnumerable<InventoryRequest> mintRequests)
    {
        var messageRequests = await mintRequests.GroupByAsync(
            async request =>
            {
                var contentObject = await _contentService.GetContent(request.ContentId);
                var handler = _contentHandlerFactory.GetHandler(contentObject);
                return await handler.ConstructMessage(transaction, id, request, contentObject);
            },
            message => message.GetType()
        );

        foreach (var request in messageRequests)
        {
            var handler = _contentHandlerFactory.GetHandler(request.Key);
            await handler.SendMessages(transaction, request.Value);
        }
    }

    public async Task UpdateItems(string transaction, string id, IEnumerable<InventoryRequestUpdate> updateItemsRequest)
    {
        var messageRequests = await updateItemsRequest.GroupByAsync(
            async request =>
            {
                var contentObject = await _contentService.GetContent(request.ContentId);
                var handler = _contentHandlerFactory.GetHandler(contentObject);
                return await handler.ConstructMessage(transaction, id, request, contentObject);
            },
            message => message.GetType()
        );

        foreach (var request in messageRequests)
        {
            var handler = _contentHandlerFactory.GetHandler(request.Key);
            await handler.SendMessages(transaction, request.Value);
        }
    }

    public async Task<FederatedInventoryProxyState> GetLastKnownState(string id)
    {
        var lastKnownState = await _inventoryStateCollection.Get(id.ToLower());
        return lastKnownState ?? new FederatedInventoryProxyState
        {
            currencies = new Dictionary<string, long>(),
            items = new Dictionary<string, List<FederatedItemProxy>>()
        };
    }
}