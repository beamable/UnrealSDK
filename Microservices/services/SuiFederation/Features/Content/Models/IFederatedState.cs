using System.Collections.Generic;
using Beamable.Common;

namespace Beamable.SuiFederation.Features.Content.Models;

public interface IFederatedState { }

public class CurrenciesState : IFederatedState
{
    public Dictionary<string, long> Currencies { get; set; } = new();
}

public class ItemsState : IFederatedState
{
    public Dictionary<string, List<FederatedItemProxy>> Items { get; set; } = new();
}