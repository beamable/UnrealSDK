using System.Collections.Generic;
using Beamable.SuiFederation.Features.Content.FunctionMessages;

namespace Beamable.SuiFederation.Features.SuiApi.Models;

public class NewItemsRequest
{
    public List<RegularCoinMintMessage> RegularCoins { get; set; } = [];
}