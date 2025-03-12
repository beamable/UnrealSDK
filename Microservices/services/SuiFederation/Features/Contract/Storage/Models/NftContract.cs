using MongoDB.Bson.Serialization.Attributes;

namespace Beamable.SuiFederation.Features.Contract.Storage.Models;

[BsonDiscriminator(nameof(NftContract))]
public class NftContract : ContractBase
{
    public required string AdminCap { get; init; }
    public required string OwnerInfo { get; init; }
}