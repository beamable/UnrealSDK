using System;
using System.Threading.Tasks;
using Beamable.Common;
using LazyCache;
using Microsoft.Extensions.Caching.Memory;

namespace Beamable.SuiFederation.Caching;

public static class GlobalCache
{
    private static CachingService Instance { get; } = new ();

    private static readonly TimeSpan DefaultExpiration = TimeSpan.FromSeconds(5);
    public static async Task<T> GetOrCreateAsync<T>(string key, Func<ICacheEntry, Task<T>> factory, TimeSpan? expiration = null)
    {
        return await Instance.GetOrAdd(key, entry =>
        {
            try
            {
                var entryExpiration = expiration ?? DefaultExpiration;
                entry.SetAbsoluteExpiration(entryExpiration);
                return factory(entry);
            }
            catch (Exception ex)
            {
                BeamableLogger.LogWarning($"Resolving cache entry for {key} threw an exception: {ex.Message}");
                throw;
            }
        });
    }
}