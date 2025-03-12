namespace Beamable.SuiFederation.Features.SuiApi.Models;

public record CoinBalanceRequest(
    string PackageId,
    string ModuleName);