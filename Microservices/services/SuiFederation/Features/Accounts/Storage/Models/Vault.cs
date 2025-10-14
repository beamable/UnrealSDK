using System.Collections.Generic;
using MongoDB.Bson.Serialization.Attributes;

namespace Beamable.SuiFederation.Features.Accounts.Storage.Models;

public record Vault(
    [property: BsonElement("_id")] string Name,
    string Address,
    string PrivateKey,
    string PublicKey,
    [property: BsonIgnoreIfNull] List<VaultBalance>? VaultBalance = null
);

public record VaultBalance(
    string CoinModule,
    long Balance
);