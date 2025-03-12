namespace Beamable.SuiFederation.Features.SuiApi.Models;

public record GameCoinBalanceResponse(
    string CoinType,
    long Total);