using System.Collections.Generic;
using Beamable.Common;
using Beamable.Common.Api.Auth;
using Beamable.SuiFederation.Extensions;
using Beamable.SuiFederation.Features.Content;
using Beamable.SuiFederation.Features.Content.Models;
using Beamable.SuiFederation.Features.Contract;
using Beamable.SuiFederation.Features.Inventory.Storage;
using Beamable.SuiFederation.Features.Inventory.Storage.Models;

namespace Beamable.SuiFederation.Endpoints;

public class GetInventoryStateEndpoint : IEndpoint
{
    private readonly InventoryStateCollection _inventoryStateCollection;
    private readonly ContractService _contractService;
    private readonly ContentHandlerFactory _contentHandlerFactory;

    public GetInventoryStateEndpoint(InventoryStateCollection inventoryStateCollection, ContractService contractService, ContentHandlerFactory contentHandlerFactory)
    {
        _inventoryStateCollection = inventoryStateCollection;
        _contractService = contractService;
        _contentHandlerFactory = contentHandlerFactory;
    }

    public async Promise<FederatedInventoryProxyState> GetInventoryState(string id, ExternalIdentity externalIdentity)
    {
        var resultState = new FederatedInventoryProxyState
        {
            currencies = new Dictionary<string, long>(),
            items = new Dictionary<string, List<FederatedItemProxy>>(),
        };

        foreach (var contentObject in await _contractService.FetchFederationContentForState(externalIdentity))
        {
            var handler = _contentHandlerFactory.GetHandler(contentObject);
            var state = await handler.GetState(id, contentObject.Id);
            switch (state)
            {
                case CurrenciesState currencyState:
                {
                    foreach (var kvp in currencyState.Currencies)
                    {
                        resultState.currencies.GetOrAdd(kvp.Key, kvp.Value);
                    }
                    break;
                }
                case ItemsState itemsState:
                {
                    foreach (var kvp in itemsState.Items)
                    {
                        if (!resultState.items.ContainsKey(kvp.Key))
                            resultState.items[kvp.Key] = [];

                        resultState.items[kvp.Key].AddRange(kvp.Value);
                    }

                    break;
                }
            }
        }

        await _inventoryStateCollection.Save(new InventoryState
        {
            Id = id.ToLower(),
            Inventory = resultState
        });

        return resultState;
    }
}