using System.Threading.Tasks;
using Beamable.Server;
using Beamable.SuiFederation.Features.Accounts.Storage.Models;
using MongoDB.Driver;

namespace Beamable.SuiFederation.Features.Accounts.Storage;

public class VaultCollection(IStorageObjectConnectionProvider storageObjectConnectionProvider)
    : IService
{
    private static readonly Collation CaseInsensitiveCollation = new("en", strength: CollationStrength.Primary);
    private IMongoCollection<Vault>? _collection;

    private async ValueTask<IMongoCollection<Vault>> Get()
    {
        if (_collection is not null) return _collection;
        _collection =
            (await storageObjectConnectionProvider.SuiFederationStorageDatabase()).GetCollection<Vault>("vault");
        await _collection.Indexes.CreateManyAsync([
            new CreateIndexModel<Vault>(Builders<Vault>.IndexKeys.Ascending(x => x.Address),
                new CreateIndexOptions
                {
                    Name = "address",
                    Unique = true,
                    Collation = CaseInsensitiveCollation
                })
        ]);
        return _collection;
    }

    public async Task<Vault?> GetVaultByName(string name)
    {
        var collection = await Get();
        return await collection.Find(x => x.Name == name).FirstOrDefaultAsync();
    }

    public async Task<string?> GetNameByAddress(string address)
    {
        var collection = await Get();
        return await collection
            .Find(x => x.Address == address, options: new FindOptions
            {
                Collation = CaseInsensitiveCollation
            })
            .Project(x => x.Name)
            .FirstOrDefaultAsync();
    }

    public async Task<bool> TryInsertVault(Vault vault)
    {
        var collection = await Get();
        try
        {
            await collection.InsertOneAsync(vault);
            return true;
        }
        catch (MongoWriteException ex) when (ex.WriteError.Category == ServerErrorCategory.DuplicateKey)
        {
            return false;
        }
    }
}