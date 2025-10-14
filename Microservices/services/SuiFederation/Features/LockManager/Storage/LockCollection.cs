using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using Beamable.Server;
using Beamable.SuiFederation.Features.LockManager.Storage.Models;
using MongoDB.Driver;

namespace Beamable.SuiFederation.Features.LockManager.Storage;

public class LockCollection(IStorageObjectConnectionProvider storageObjectConnectionProvider)
    : IService
{
    private IMongoCollection<Lock>? _collection;

    private async ValueTask<IMongoCollection<Lock>> Get()
    {
        if (_collection is null)
        {
            _collection =
                (await storageObjectConnectionProvider.SuiFederationStorageDatabase()).GetCollection<Lock>("lock");
            await _collection.Indexes.CreateManyAsync(new[]
            {
                new CreateIndexModel<Lock>(Builders<Lock>.IndexKeys
                        .Ascending(x => x.LockId)
                        .Ascending(x => x.InstanceId),
                    new CreateIndexOptions
                    {
                        Unique = true
                    }),
                new CreateIndexModel<Lock>(Builders<Lock>.IndexKeys.Ascending(x => x.Expiration),
                    new CreateIndexOptions
                    {
                        Name = "expiry",
                        ExpireAfter = TimeSpan.Zero
                    }),
            });
        }
        return _collection;
    }

    public async Task<bool> AcquireLock(string name, string instanceId, int lockTimeoutSeconds)
    {
        var collection = await Get();
        try
        {
            var newLock = new Lock(name, instanceId, DateTime.UtcNow.AddSeconds(lockTimeoutSeconds));
            await collection.InsertOneAsync(newLock);
            return true;
        }
        catch (MongoWriteException ex) when (ex.WriteError.Category == ServerErrorCategory.DuplicateKey)
        {
            return false;
        }
    }

    public async Task ReleaseLock(string name)
    {
        var collection = await Get();
        var filter = Builders<Lock>.Filter.Eq(x => x.LockId, name);
        await collection.DeleteOneAsync(filter, CancellationToken.None);
    }

    public async Task<List<string>> GetLocked()
    {
        var collection = await Get();
        var locks = await collection.Find(_ => true).Project(l => l.LockId).ToListAsync();
        return locks ?? [];
    }
}