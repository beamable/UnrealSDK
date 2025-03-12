using MongoDB.Bson.Serialization.Attributes;

namespace Beamable.SuiFederation.Features.Contract.Storage.Models;

[BsonDiscriminator(nameof(GameCoinContract))]
public class GameCoinContract : ContractBase
{
    public required string AdminCap { get; init; }
    public required string TokenPolicyCap { get; init; }
    public required string TokenPolicy { get; init; }
    public required string Store { get; init; }
}