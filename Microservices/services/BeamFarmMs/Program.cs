using Beamable.Server;
using System.Threading.Tasks;

namespace Beamable.BeamFarmMs
{
	public class Program
	{
		/// <summary>
		/// The entry point for the <see cref="BeamFarmMs"/> service.
		/// </summary>
		public static async Task Main()
		{
			await BeamServer
				.Create()
				.IncludeRoutes<BeamFarmMs>(routePrefix: "")
				.RunForever();
		}
	}
}
