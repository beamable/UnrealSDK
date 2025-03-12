using System;
using System.Collections.Concurrent;
using System.Reflection;
using Beamable.Common;
using Beamable.Server;

namespace Beamable.SuiFederation.Extensions;

public static class MicroserviceMetadataExtensions
{
    private static readonly ConcurrentDictionary<Type, MicroserviceInfo> Cache = new();

    public static MicroserviceInfo GetMetadata<TService, TIdentity>()
        where TService : Microservice, IFederatedLogin<TIdentity>, new()
        where TIdentity : IFederationId, new()
    {
        return Cache.GetOrAdd(typeof(TService), _ =>
        {
            var microservice = new TService();
            var microserviceName = microservice.GetType().GetCustomAttribute<MicroserviceAttribute>()!.MicroserviceName;
            var identity = new TIdentity();
            var microserviceNamespace = identity.GetUniqueName();
            return new MicroserviceInfo(microserviceName, microserviceNamespace);
        });
    }
}

public record MicroserviceInfo(string MicroserviceName, string MicroserviceNamespace);