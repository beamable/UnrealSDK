using SuiFederationCommon.Extensions;

namespace Beamable.SuiFederation.Features.Inventory.Models;

public record InventoryRequestDelete(
    long GamerTag,
    string ContentId,
    string ProxyId);


public static class InventoryRequestDeleteExtensions
{
    public static string ToNftType(this InventoryRequestDelete inventoryRequest)
        => inventoryRequest.ContentId.ToContentType();
}