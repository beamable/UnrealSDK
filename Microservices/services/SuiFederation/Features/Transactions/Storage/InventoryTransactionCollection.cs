using System;
using System.Threading.Tasks;
using Beamable.Server;
using Beamable.SuiFederation.Features.Transactions.Storage.Models;
using MongoDB.Driver;

namespace Beamable.SuiFederation.Features.Transactions.Storage;

public class InventoryTransactionCollection : IService
{
    private readonly IStorageObjectConnectionProvider _storageObjectConnectionProvider;
    private IMongoCollection<TransactionRecord>? _collection;

    public InventoryTransactionCollection(IStorageObjectConnectionProvider storageObjectConnectionProvider)
    {
        _storageObjectConnectionProvider = storageObjectConnectionProvider;
    }

    private async ValueTask<IMongoCollection<TransactionRecord>> Get()
    {
        if (_collection is null)
        {
            var db = await _storageObjectConnectionProvider.SuiFederationStorageDatabase();
            _collection = db.GetCollection<TransactionRecord>("inventory-transaction");
            await _collection.Indexes.CreateOneAsync(new CreateIndexModel<TransactionRecord>(Builders<TransactionRecord>.
                IndexKeys.Ascending(x => x.ExpireAt), new CreateIndexOptions { ExpireAfter = TimeSpan.Zero }));
        }
        return _collection;
    }

    public async Task<bool> TryInsertInventoryTransaction(string transactionId)
    {
        var collection = await Get();
        try
        {
            await collection.InsertOneAsync(new TransactionRecord
            {
                Id = transactionId
            });
            return true;
        }
        catch (MongoWriteException ex) when (ex.WriteError.Category == ServerErrorCategory.DuplicateKey)
        {
            return false;
        }
    }

    public async Task DeleteInventoryTransaction(string transactionId)
    {
        var collection = await Get();
        await collection.DeleteOneAsync(x => x.Id == transactionId);
    }
}