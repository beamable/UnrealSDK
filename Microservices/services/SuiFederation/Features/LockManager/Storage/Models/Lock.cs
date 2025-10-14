using System;
using MongoDB.Bson.Serialization.Attributes;

namespace Beamable.SuiFederation.Features.LockManager.Storage.Models;

public record Lock(
    [property: BsonId] string LockId,
    string InstanceId,
    DateTime Expiration);