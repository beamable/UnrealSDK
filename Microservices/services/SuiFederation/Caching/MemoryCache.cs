using System;
using System.Collections.Concurrent;
using System.Threading;
using System.Threading.Tasks;
using Beamable.Common;

namespace Beamable.SuiFederation.Caching;

public class CacheItem<T>
{
    public required T Value { get; set; }
    public DateTime Expiration { get; set; }
}

public class MemoryCache<T> : IDisposable
{
    private readonly ConcurrentDictionary<string, CacheItem<T>> _cache = new();
    private readonly ConcurrentQueue<string> _expirationKeys = new();
    private readonly TimeSpan _cleanupInterval;
    private readonly object _cleanupLock = new();
    private readonly CancellationTokenSource _cleanupCts = new();
    private readonly Task _cleanupTask;
    private bool _disposed = false;

    public MemoryCache(TimeSpan cleanupInterval)
    {
        if (cleanupInterval < TimeSpan.FromMinutes(1))
            throw new ArgumentOutOfRangeException($"{nameof(cleanupInterval)} can't be less than {TimeSpan.FromMinutes(1)}");
        _cleanupInterval = cleanupInterval;
        _cleanupTask = Task.Run(() => CleanupBackgroundTask(_cleanupCts.Token));
        SetupShutdownHook();
    }

    public async Task<T?> GetOrAddAsync(string key, Func<Task<T?>> valueFactory)
    {
        if (_cache.TryGetValue(key, out var cacheItem) && cacheItem.Expiration > DateTime.UtcNow)
        {
            return cacheItem.Value;
        }

        var newValue = await valueFactory();
        if (newValue is null)
            return default;

        var newCacheItem = new CacheItem<T>
        {
            Value = newValue,
            Expiration = DateTime.UtcNow.Add(_cleanupInterval)
        };

        var addedItem = _cache.AddOrUpdate(key, newCacheItem, (_, oldItem) => oldItem.Expiration > DateTime.UtcNow ? oldItem : newCacheItem);

        _expirationKeys.Enqueue(key);

        return addedItem.Value;
    }

    private async Task CleanupBackgroundTask(CancellationToken cancellationToken)
    {
        while (!cancellationToken.IsCancellationRequested)
        {
            CleanupExpiredItems();
            await Task.Delay(_cleanupInterval, cancellationToken);
        }
    }

    private void CleanupExpiredItems()
    {
        try
        {
            var now = DateTime.UtcNow;
            while (_expirationKeys.TryPeek(out var oldest))
            {
                // Check if the key exists in the cache BEFORE dequeuing
                if (!_cache.TryGetValue(oldest, out var cacheItem))
                {
                    // If the key is missing from _cache, remove it from the queue as well
                    _expirationKeys.TryDequeue(out _);
                    continue;
                }
                // If it's not expired, stop the loop (since it's FIFO, all later items are also not expired)
                if (cacheItem.Expiration > now)
                {
                    break;
                }
                // If expired, remove from both _cache and _expirationKeys
                if (_expirationKeys.TryDequeue(out var expiredKey))
                {
                    _cache.TryRemove(expiredKey, out _);
                }
            }
        }
        catch (Exception e)
        {
            BeamableLogger.LogWarning($"CleanupExpiredItems failed: {e}");
        }
    }


    private void SetupShutdownHook()
    {
        AppDomain.CurrentDomain.ProcessExit += OnProcessExit;
    }

    private void OnProcessExit(object? sender, EventArgs e)
    {
        Dispose();
        AppDomain.CurrentDomain.ProcessExit -= OnProcessExit;
    }

    public void Dispose()
    {
        Dispose(true);
        GC.SuppressFinalize(this);
    }

    private void Dispose(bool disposing)
    {
        if (!_disposed)
        {
            if (disposing)
            {
                _cleanupCts.Cancel();
                _cleanupCts.Dispose();
            }
            _disposed = true;
        }
    }

    ~MemoryCache()
    {
        Dispose(false);
    }
}