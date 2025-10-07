using Beamable.Server;
using System.Threading.Tasks;

namespace Beamable.SteamDemo
{
	public class Program
	{
		/// <summary>
		/// The entry point for the <see cref="SteamDemo"/> service.
		/// </summary>
		public static async Task Main()
		{
			// Creating the builder that we use to setup the config of microservice
			var beamConfigBuilder = BeamServer.Create();

			beamConfigBuilder.IncludeRoutes<SteamDemo>(routePrefix: "");
			
			// Start the microservice and keep the process running
			await beamConfigBuilder.RunForever();
		}
	}
}
