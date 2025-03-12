using System.Collections.Generic;
using System.Linq;
using Beamable.Common;
using Beamable.Common.Api.Inventory;

namespace Beamable.SuiFederation.Features.SuiApi.Models;

public record GetOwnedObjectsResponse(
    string ObjectId,
    string Type,
    string Name,
    string Description,
    string Image,
    string ContentId,
    ResponseAttribute[] Attributes);
public record ResponseAttribute(string Name, string Value);

public static class GetOwnedObjectsResponseExtensions
{
    public static Dictionary<string, List<FederatedItemProxy>> ToInventoryState(this IEnumerable<GetOwnedObjectsResponse> response)
    {
        return response
            .GroupBy(o => o.ContentId)
            .ToDictionary(
                g => g.Key,
                g => g.Select(o => new FederatedItemProxy
                {
                    proxyId = o.ObjectId,
                    properties = new List<ItemProperty>
                        {
                            new() { name = "name", value = o.Name },
                            new() { name = "type", value = o.Type },
                            new() { name = "description", value = o.Description },
                            new() { name = "image", value = o.Image }
                        }
                        .Concat(o.Attributes.Select(a => new ItemProperty { name = a.Name, value = a.Value }))
                        .ToList()
                }).ToList()
            );
    }
}