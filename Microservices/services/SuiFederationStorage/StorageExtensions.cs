using Beamable.Common;
using MongoDB.Driver;

namespace Beamable.Server
{
	public static class SuiFederationStorageExtension
	{
		/// <summary>
		/// Get an authenticated MongoDB instance for SuiFederationStorage
		/// </summary>
		/// <returns></returns>
		public static Promise<IMongoDatabase> SuiFederationStorageDatabase(
			this IStorageObjectConnectionProvider provider)
			=> provider.GetDatabase<SuiFederationStorage>();

		/// <summary>
		/// Gets a MongoDB collection from SuiFederationStorage by the requested name, and uses the given mapping class.
		/// </summary>
		/// <param name="provider"></param>
		/// <param name="name">The name of the collection</param>
		/// <typeparam name="TCollection">The type of the mapping class</typeparam>
		/// <returns>When the promise completes, you'll have an authorized collection</returns>
		public static Promise<IMongoCollection<TCollection>> SuiFederationStorageCollection<TCollection>(
			this IStorageObjectConnectionProvider provider, string name)
			where TCollection : StorageDocument
			=> provider.GetCollection<SuiFederationStorage, TCollection>(name);

		/// <summary>
		/// Gets a MongoDB collection from SuiFederationStorage by the requested name, and uses the given mapping class.
		/// </summary>
		/// <param name="provider">The name of the collection</param>
		/// <typeparam name="TCollection">The type of the mapping class</typeparam>
		/// <returns>When the promise completes, you'll have an authorized collection</returns>
		public static Promise<IMongoCollection<TCollection>> SuiFederationStorageCollection<TCollection>(
			this IStorageObjectConnectionProvider provider)
			where TCollection : StorageDocument
			=> provider.GetCollection<SuiFederationStorage, TCollection>();
	}
}