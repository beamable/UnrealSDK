using System;
using System.Collections.Generic;
using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace Beamable.SuiFederation.Features.Inventory.Storage.Models;

public class Mint
{
    [BsonId]
    public ObjectId Id { get; set; } = new();
    public string ContentId { get; set; } = null!;
    public string PackageId { get; set; } = null!;
    public string Module { get; set; } = null!;
    public string Digest { get; set; } = null!;
    public string InitialOwnerAddress { get; set; } = null!;

    public Dictionary<string, string> Metadata { get; set; } = new();

    public DateTime Minted { get; set; } = DateTime.UtcNow;
}