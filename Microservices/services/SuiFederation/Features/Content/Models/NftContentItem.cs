using System;
using System.Collections.Generic;
using System.Linq;
using Beamable.SuiFederation.Features.Inventory.Models;
using SuiFederationCommon.Models;

namespace Beamable.SuiFederation.Features.Content.Models;

public record NftContentItem(
    string Name,
    string Url,
    string Description,
    string ContentId,
    NftAttribute[] Attributes);

public record NftAttribute(string Name, string Value);

public static class NftContentItemExtensions
{
    public static NftContentItem Create(InventoryRequest inventoryRequest, INftBase nftBase)
    {
        var requestProperties = inventoryRequest.Properties ?? new Dictionary<string, string>();
        var name = requestProperties.FirstOrDefault(kv => kv.Key.StartsWith("$name", StringComparison.OrdinalIgnoreCase)).Value ?? nftBase.Name;
        var image = requestProperties.FirstOrDefault(kv => kv.Key.StartsWith("$image", StringComparison.OrdinalIgnoreCase)).Value ?? nftBase.Image;
        var description = requestProperties.FirstOrDefault(kv => kv.Key.StartsWith("$description", StringComparison.OrdinalIgnoreCase)).Value ?? nftBase.Description;
        var attributes = GetAttributes(requestProperties, nftBase.CustomProperties);
        return new NftContentItem(name,image,description,inventoryRequest.ContentId,attributes.Select(kv => new NftAttribute(kv.Key, kv.Value)).ToArray());
    }

    private static Dictionary<string, string> GetAttributes(Dictionary<string, string> dynamicProperties, Dictionary<string, string> staticProperties)
    {
        var filteredDynamic = dynamicProperties
            .Where(kvp => kvp.Key.StartsWith('$') &&
                          !kvp.Key.StartsWith("$name") &&
                          !kvp.Key.StartsWith("$image") &&
                          !kvp.Key.StartsWith("$description"))
            .ToDictionary(kvp => kvp.Key.TrimStart('$'), kvp => kvp.Value);
        var result = new Dictionary<string, string>(staticProperties);
        foreach (var kvp in filteredDynamic)
        {
            result[kvp.Key] = kvp.Value;
        }
        return result;
    }

    public static Dictionary<string, string> GetAttributes(this NftContentItem item)
    {
        var result = new Dictionary<string, string>
        {
            { nameof(item.Name), item.Name },
            { nameof(item.Description), item.Description },
            { nameof(item.Url), item.Url }
        };
        foreach (var kvp in item.Attributes)
        {
            result[kvp.Name] = kvp.Value;
        }
        return result;

    }

    public static HashSet<string> FixedProperties()
        => ["name", "image", "description", "type"];
}