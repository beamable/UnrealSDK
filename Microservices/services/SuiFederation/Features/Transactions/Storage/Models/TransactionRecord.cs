using System;
using MongoDB.Bson.Serialization.Attributes;

namespace Beamable.SuiFederation.Features.Transactions.Storage.Models;

internal record TransactionRecord
{
    [BsonElement("_id")]
    public string Id { get; set; } = null!;
    public DateTime ExpireAt { get; set; } = DateTime.UtcNow.AddHours(1);
}