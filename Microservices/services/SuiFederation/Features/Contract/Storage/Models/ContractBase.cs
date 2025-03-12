using System;
using MongoDB.Bson.Serialization.Attributes;

namespace Beamable.SuiFederation.Features.Contract.Storage.Models;

public class ContractBase
{
    [BsonId]
    public required string ContentId { get; init; }
    public required string PackageId { get; init; }
    public required string Module { get; init; }

    public DateTime Created { get; set; } = DateTime.UtcNow;
}