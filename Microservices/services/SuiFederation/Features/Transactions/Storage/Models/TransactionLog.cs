using System;
using System.Collections.Generic;
using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace Beamable.SuiFederation.Features.Transactions.Storage.Models;

[BsonIgnoreExtraElements]
public class TransactionLog
{
    [BsonId]
    public ObjectId Id { get; set; }
    public string? InventoryTransactionId { get; set; }
    public long RequesterUserId { get; set; }
    public string Wallet { get; set; } = null!;
    public string OperationName { get; set; } = null!;
    public string Path { get; set; } = null!;

    public DateTime StartTimestamp { get; set; } = DateTime.UtcNow;
    public DateTime? EndTimestamp { get; set; }
    public DateTime? MintedTimestamp { get; set; }
    public string Request { get; set; } = null!;

    [BsonIgnoreIfNull]
    public string? Error { get; set; }

    public List<ChainTransaction> ChainTransactions { get; set; } = new();
}

[BsonIgnoreExtraElements]
public class ChainTransaction
{
    public string Function { get; set; } = null!;
    public string Data { get; set; } = null!;
    public string Status { get; set; } = null!;

    [BsonIgnoreIfNull]
    public string GasUsed { get; set; } = null!;

    [BsonIgnoreIfNull]
    public string? Digest { get; set; }

    [BsonIgnoreIfNull]
    public string? Error { get; set; }

    public DateTime Timestamp { get; set; } = DateTime.UtcNow;
}