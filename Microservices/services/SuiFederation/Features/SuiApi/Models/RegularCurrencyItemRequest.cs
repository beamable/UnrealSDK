namespace Beamable.SuiFederation.Features.SuiApi.Models;

public record RegularCurrencyItemRequest(
    string PackageId,
    string Module,
    long Amount,
    string TreasuryCap,
    string PlayerAddress);