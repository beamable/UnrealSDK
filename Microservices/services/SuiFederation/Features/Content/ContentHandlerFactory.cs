using System;
using Beamable.Common.Content;
using Beamable.Common.Dependencies;
using Beamable.SuiFederation.Features.Content.FunctionMessages;
using Beamable.SuiFederation.Features.Content.Handlers;
using Microsoft.Extensions.DependencyInjection;
using SuiFederationCommon.FederationContent;
using SuiFederationCommon.Models;

namespace Beamable.SuiFederation.Features.Content;

public class ContentHandlerFactory(
    IDependencyProvider serviceProvider) : IService
{
    public IContentHandler GetHandler(IContentObject contentObject)
    {
        return contentObject switch
        {
            CoinCurrency => serviceProvider.GetRequiredService<RegularCoinHandler>(),
            InGameCurrency => serviceProvider.GetRequiredService<GameCoinHandler>(),
            INftBase => serviceProvider.GetRequiredService<NftHandler>(),
            _ => throw new NotSupportedException($"ContentId '{contentObject.Id}' is not supported.")
        };
    }
}