namespace Beamable.SuiFederation.Features.SuiApi.Models;

public record CoinBalanceResponse(
    string CoinType,
    long Total);