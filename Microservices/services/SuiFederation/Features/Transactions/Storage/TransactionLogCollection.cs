using System;
using System.Linq;
using System.Threading.Tasks;
using Beamable.Server;
using Beamable.SuiFederation.Features.Transactions.Storage.Models;
using MongoDB.Bson;
using MongoDB.Driver;

namespace Beamable.SuiFederation.Features.Transactions.Storage;

public class TransactionLogCollection : IService
{
	private readonly IStorageObjectConnectionProvider _storageObjectConnectionProvider;
	private IMongoCollection<TransactionLog>? _collection;

	public TransactionLogCollection(IStorageObjectConnectionProvider storageObjectConnectionProvider)
	{
		_storageObjectConnectionProvider = storageObjectConnectionProvider;
	}

	private async ValueTask<IMongoCollection<TransactionLog>> Get()
	{
		if (_collection is null)
		{
			var db = await _storageObjectConnectionProvider.SuiFederationStorageDatabase();
			_collection = db.GetCollection<TransactionLog>("transaction-log");

			await _collection.Indexes.CreateOneAsync(new CreateIndexModel<TransactionLog>(Builders<TransactionLog>.IndexKeys
				.Ascending(x => x.Wallet)
				.Ascending(x => x.OperationName)
			));
			await _collection.Indexes.CreateOneAsync(new CreateIndexModel<TransactionLog>(Builders<TransactionLog>.IndexKeys
				.Ascending("ChainTransactions.Digest")
			));;
		}
		return _collection;
	}

	public async Task Insert(TransactionLog log)
	{
		var collection = await Get();
		await collection.InsertOneAsync(log);
	}

	public async Task SetDone(ObjectId inventoryTransaction)
	{
		var collection = await Get();
		var update = Builders<TransactionLog>.Update.Set(x => x.EndTimestamp, DateTime.UtcNow);
		await collection.UpdateOneAsync(x => x.Id == inventoryTransaction, update);
	}

	public async Task SetMintedDone(ObjectId inventoryTransaction)
	{
		var collection = await Get();
		var update = Builders<TransactionLog>.Update.Set(x => x.MintedTimestamp, DateTime.UtcNow);
		await collection.UpdateOneAsync(x => x.Id == inventoryTransaction, update);
	}

	public async Task SetError(ObjectId transactionId, string error)
	{
		var collection = await Get();
		var update = Builders<TransactionLog>.Update.Set(x => x.Error, error);
		await collection.UpdateOneAsync(x => x.Id == transactionId, update);
	}

	public async Task AddChainTransaction(ObjectId transactionId, ChainTransaction chainTransaction)
	{
		var collection = await Get();
		var update = Builders<TransactionLog>.Update.Push(x => x.ChainTransactions, chainTransaction);
		await collection.UpdateOneAsync(x => x.Id == transactionId, update);
	}

	public async Task<string> GetInventoryTransaction(ObjectId id)
	{
		var collection = await Get();
		return (await collection.Find(x => x.Id == id).FirstOrDefaultAsync()).InventoryTransactionId ?? "";
	}

	public async Task<TransactionLog?> GetByInventoryTransaction(string inventoryTransaction)
	{
		var collection = await Get();
		return await collection.Find(x => x.InventoryTransactionId == inventoryTransaction).FirstOrDefaultAsync();
	}
}