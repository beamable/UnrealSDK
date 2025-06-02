using System.Collections.Generic;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Server;
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

    public async Task NewItems(string transaction, string wallet, IEnumerable<InventoryRequest> mintRequests, UserRequestDataHandler user)
    {
        var messageRequests = await mintRequests.ParallelGroupByAsync(
            async request =>
            {
                var contentObject = await _contentService.GetContent(request.ContentId);
                var handler = _contentHandlerFactory.GetHandler(contentObject);
                var messages = await handler.ConstructMessage(transaction, wallet, request, contentObject);
                return (key: handler, value: messages);
            }
        );

        foreach (var request in messageRequests)
        {
            await request.Key.SendMessages(transaction, request.Value);
        }
    }

    public async Task UpdateItems(string transaction, string wallet, IEnumerable<InventoryRequestUpdate> updateItemsRequest, UserRequestDataHandler user)
    {
        var messageRequests = await updateItemsRequest.ParallelGroupByAsync(
            async request =>
            {
                var contentObject = await _contentService.GetContent(request.ContentId);
                var handler = _contentHandlerFactory.GetHandler(contentObject);
                var messages = await handler.ConstructMessage(transaction, wallet, request, contentObject);
                return (key: handler, value: messages);
            }
        );

        foreach (var request in messageRequests)
        {
            await request.Key.SendMessages(transaction, request.Value);
        }
    }

    public async Task DeleteItems(string transaction, string wallet, IEnumerable<InventoryRequestDelete> deleteItemsRequest, UserRequestDataHandler user)
    {
        var messageRequests = await deleteItemsRequest.ParallelGroupByAsync(
            async request =>
            {
                var contentObject = await _contentService.GetContent(request.ContentId);
                var handler = _contentHandlerFactory.GetHandler(contentObject);
                var messages = await handler.ConstructMessage(transaction, wallet, request, contentObject);
                return (key: handler, value: messages);
            }
        );

        foreach (var request in messageRequests)
        {
            await request.Key.SendMessages(transaction, request.Value);
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