using Beamable.Server;

namespace Beamable.Server
{
	/// <summary>
	/// This class represents the existence of the BeamballDb database.
	/// Use it for type safe access to the database.
	/// <code>
	/// var db = await Storage.GetDatabase&lt;BeamballDb&gt;();
	/// </code>
	/// </summary>
	[StorageObject("BeamballDb")]
	public class BeamballDb : MongoStorageObject
	{
		
	}
}
