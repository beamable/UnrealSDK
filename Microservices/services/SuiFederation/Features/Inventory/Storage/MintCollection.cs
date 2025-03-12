using System.Collections.Generic;
using System.Threading.Tasks;
using Beamable.Server;
using Beamable.SuiFederation.Features.Inventory.Storage.Models;
using MongoDB.Driver;

namespace Beamable.SuiFederation.Features.Inventory.Storage;

public class MintCollection : IService
{
	private readonly IStorageObjectConnectionProvider _storageObjectConnectionProvider;
	private IMongoCollection<Mint>? _collection;

	public MintCollection(IStorageObjectConnectionProvider storageObjectConnectionProvider)
	{
		_storageObjectConnectionProvider = storageObjectConnectionProvider;
	}

	private async ValueTask<IMongoCollection<Mint>> Get()
	{
		if (_collection is null)
		{
			var db = await _storageObjectConnectionProvider.SuiFederationStorageDatabase();
			_collection = db.GetCollection<Mint>("mint");
			await _collection.Indexes.CreateManyAsync([
				new CreateIndexModel<Mint>(Builders<Mint>.IndexKeys.Ascending(x => x.PackageId).Ascending(x => x.ContentId)),
				new CreateIndexModel<Mint>(Builders<Mint>.IndexKeys.Ascending(x => x.PackageId).Ascending(x => x.ContentId).Ascending(x => x.InitialOwnerAddress))
			]);
		}

		return _collection;
	}

	public async Task InsertMints(IEnumerable<Mint> mints)
	{
		var collection = await Get();
		var options = new InsertManyOptions
		{
			IsOrdered = false
		};
		await collection.InsertManyAsync(mints, options);
	}
}