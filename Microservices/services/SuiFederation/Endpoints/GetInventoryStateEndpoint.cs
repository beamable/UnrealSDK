using System.Collections.Generic;
using Beamable.Common;
using Beamable.SuiFederation.Extensions;
using Beamable.SuiFederation.Features.Content;
using Beamable.SuiFederation.Features.Content.Models;
using Beamable.SuiFederation.Features.Contract;
using Beamable.SuiFederation.Features.Inventory.Storage;
using Beamable.SuiFederation.Features.Inventory.Storage.Models;

namespace Beamable.SuiFederation.Endpoints;

public class GetInventoryStateEndpoint(
    InventoryStateCollection inventoryStateCollection,
    ContractService contractService,
    ContentHandlerFactory contentHandlerFactory) : IEndpoint
{
    public async Promise<FederatedInventoryProxyState> GetInventoryState(string id)
    {
        var resultState = new FederatedInventoryProxyState
        {
            currencies = new Dictionary<string, long>(),
            items = new Dictionary<string, List<FederatedItemProxy>>(),
        };

        await foreach (var contentObject in contractService.FetchFederationContent())
        {
            var handler = contentHandlerFactory.GetHandler(contentObject);
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

        await inventoryStateCollection.Save(new InventoryState
        {
            Id = id.ToLower(),
            Inventory = resultState
        });

        return resultState;
    }
}