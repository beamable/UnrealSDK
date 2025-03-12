using System;
using System.Threading.Tasks;
using Beamable.Common.Content;
using Beamable.Common.Dependencies;
using SuiFederationCommon.FederationContent;
using SuiFederationCommon.Models;

namespace Beamable.SuiFederation.Features.Contract.Handlers;

public class ContentContractHandlerResolver(IDependencyProvider dependencyProvider) : IService
{
    public async Task HandleContent(IContentObject clientContentInfo)
    {
        ContractTemplateService.Initialize();
        switch (clientContentInfo)
        {
            case CoinCurrency coinCurrency:
                await dependencyProvider.GetService<CoinCurrencyHandler>().HandleContract(coinCurrency);
                break;
            case InGameCurrency gameCurrency:
                await dependencyProvider.GetService<GameCurrencyHandler>().HandleContract(gameCurrency);
                break;
            case INftBase nftBase:
                if (nftBase is IContentObject nftBaseContent)
                    await dependencyProvider.GetService<NftContractHandler>().HandleContract(nftBaseContent);
                break;
            default:
                throw new InvalidOperationException($"No handler found for content type: {clientContentInfo.GetType().Name}");
        }
    }
}