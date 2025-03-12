namespace Beamable.SuiFederation.Features.SuiApi.Models;

public record UpdateItemRequest(
    string ItemId,
    string PackageId,
    string Module,
    string Function,
    string Data,
    string Name,
    string Value,
    string PlayerWalletKey);