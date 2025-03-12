using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Server;
using Beamable.SuiFederation.Features.Contract.Storage.Models;
using MongoDB.Driver;

namespace Beamable.SuiFederation.Features.Contract.Storage;

public class ContractCollection(IStorageObjectConnectionProvider storageObjectConnectionProvider)
    : IService
{
    private readonly Promise<IMongoDatabase> _databaseTask = storageObjectConnectionProvider.SuiFederationStorageDatabase();
    private readonly ConcurrentDictionary<Type, object> _collections = new();
    private readonly ConcurrentDictionary<Type, Task> _indexCreationTasks = new();

    private async ValueTask<IMongoCollection<TContract>> Get<TContract>() where TContract : ContractBase
    {
        var database = await _databaseTask;
        var collection = (IMongoCollection<TContract>)_collections.GetOrAdd(
            typeof(TContract), _ => database.GetCollection<TContract>("contracts")
        );
        await EnsureIndexesAsync(collection);
        return collection;
    }

    private async ValueTask EnsureIndexesAsync<TContract>(IMongoCollection<TContract> collection) where TContract : ContractBase
    {
        if (!_indexCreationTasks.ContainsKey(typeof(TContract)))
        {
            _indexCreationTasks[typeof(TContract)] = Task.Run(async () =>
            {
                await collection.Indexes.CreateManyAsync([
                    new CreateIndexModel<TContract>(Builders<TContract>.IndexKeys
                        .Ascending(x => x.PackageId)
                        .Ascending(x => x.Module))
                ]);
            });
        }

        await _indexCreationTasks[typeof(TContract)];
    }

    public async Task<bool> TryInsert<TContract>(TContract contract) where TContract : ContractBase
    {
        var collection = await Get<TContract>();
        try
        {
            await collection.InsertOneAsync(contract);
            return true;
        }
        catch (MongoWriteException ex) when (ex.WriteError.Category == ServerErrorCategory.DuplicateKey)
        {
            return false;
        }
    }

    public async Task<bool> TryUpsert<TContract>(TContract contract, string id) where TContract : ContractBase
    {
        var collection = await Get<TContract>();
        var filter = Builders<TContract>.Filter.Eq("_id", id);
        var options = new ReplaceOptions { IsUpsert = true };
        var result = await collection.ReplaceOneAsync(filter, contract, options);
        return result.IsAcknowledged;
    }

    public async Task<TContract?> GetByContentId<TContract>(string contentId) where TContract : ContractBase
    {
        var collection = await Get<TContract>();
        return await collection.Find(x => x.ContentId == contentId).FirstOrDefaultAsync();
    }

    public async Task<List<TContract>> GetAllContractsOf<TContract>() where TContract : ContractBase
    {
        var collection = await Get<ContractBase>();
        var filter = Builders<ContractBase>.Filter.Eq("_t", typeof(TContract).Name);
        var results = await collection.Find(filter).ToListAsync();
        return results.OfType<TContract>().ToList();
    }
}