using MongoDB.Bson.Serialization.Attributes;

namespace Beamable.SuiFederation.Features.Contract.Storage.Models;

[BsonDiscriminator(nameof(CoinContract))]
public class CoinContract : ContractBase
{
    public required string AdminCap { get; init; }
    public required string TreasuryCap { get; init; }
}