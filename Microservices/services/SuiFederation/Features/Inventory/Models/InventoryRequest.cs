using System.Collections.Generic;
using SuiFederationCommon.Extensions;

namespace Beamable.SuiFederation.Features.Inventory.Models;

public record InventoryRequest(
    long GamerTag,
    string ContentId,
    long Amount,
    Dictionary<string, string> Properties);


public static class InventoryRequestExtensions
{
    public static string ToNftType(this InventoryRequest inventoryRequest)
        => inventoryRequest.ContentId.ToContentType();
}