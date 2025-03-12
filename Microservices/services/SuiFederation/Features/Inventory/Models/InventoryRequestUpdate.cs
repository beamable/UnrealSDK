using System.Collections.Generic;
using SuiFederationCommon.Extensions;

namespace Beamable.SuiFederation.Features.Inventory.Models;

public record InventoryRequestUpdate(
    long GamerTag,
    string ContentId,
    string ProxyId,
    Dictionary<string, string> Properties);


public static class InventoryRequestUpdateExtensions
{
    public static string ToNftType(this InventoryRequestUpdate inventoryRequest)
        => inventoryRequest.ContentId.ToContentType();
}