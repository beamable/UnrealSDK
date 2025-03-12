using Beamable.Server;

namespace Beamable.Server
{
	/// <summary>
	/// This class represents the existence of the SuiFederationStorage database.
	/// Use it for type safe access to the database.
	/// <code>
	/// var db = await Storage.GetDatabase&lt;SuiFederationStorage&gt;();
	/// </code>
	/// </summary>
	[StorageObject("SuiFederationStorage")]
	public class SuiFederationStorage : MongoStorageObject
	{
		
	}
}
