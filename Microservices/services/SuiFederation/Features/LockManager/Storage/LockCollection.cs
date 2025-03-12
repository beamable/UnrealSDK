using System;
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
                new CreateIndexModel<Lock>(Builders<Lock>.IndexKeys.Ascending(x => x.Name),
                    new CreateIndexOptions
                    {
                        Name = "name",
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

    public async Task<bool> AcquireLock(string name, int lockTimeoutSeconds)
    {
        var collection = await Get();
        var filter = Builders<Lock>.Filter.Eq(x => x.Name, name);

        var update = Builders<Lock>.Update
            .SetOnInsert(x => x.Name, name)
            .SetOnInsert(x => x.Expiration, DateTime.UtcNow.AddSeconds(lockTimeoutSeconds));

        var options = new FindOneAndUpdateOptions<Lock>
        {
            IsUpsert = true,
            ReturnDocument = ReturnDocument.After
        };

        var result = await collection.FindOneAndUpdateAsync(filter, update, options);
        return result != null;
    }

    public async Task ReleaseLock(string name)
    {
        var collection = await Get();
        var filter = Builders<Lock>.Filter.Eq(x => x.Name, name);
        await collection.DeleteOneAsync(filter);
    }
}