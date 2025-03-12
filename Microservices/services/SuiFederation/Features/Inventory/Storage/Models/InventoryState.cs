using System;
using Beamable.Common;
using MongoDB.Bson.Serialization.Attributes;

namespace Beamable.SuiFederation.Features.Inventory.Storage.Models;

public class InventoryState
{
    [BsonElement("_id")]
    public string Id { get; set; } = null!;

    public FederatedInventoryProxyState Inventory { get; set; } = null!;

    public DateTime LastUpdate { get; set; } = DateTime.UtcNow;
}