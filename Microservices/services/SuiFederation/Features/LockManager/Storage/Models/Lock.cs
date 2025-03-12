using System;
using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace Beamable.SuiFederation.Features.LockManager.Storage.Models;

public record Lock(
    [property: BsonId, BsonRepresentation(BsonType.ObjectId)] string ID,
    string Name,
    DateTime Expiration);