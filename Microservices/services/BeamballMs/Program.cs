using System;
using Beamable.Server;
using System.Threading.Tasks;

namespace Beamable.BeamballMs
{
	public class Program
	{
		/// <summary>
		/// The entry point for the <see cref="BeamballMs"/> service.
		/// </summary>
		public static async Task Main()
		{
			// Creating the builder that we use to setup the config of microservice
			var beamConfigBuilder = BeamServer.Create();

			beamConfigBuilder.IncludeRoutes<BeamballMs>(routePrefix: "");
			
			// Set up an initialization function that runs when the service is connected and authenticated with beamable but before it accepts traffic.
			beamConfigBuilder.InitializeServices(async scope =>
			{
				await Task.WhenAll(new[]
				{
					BeamballMs.InitializeSteam(scope),
					BeamballMs.InitializeEos(scope)
				});
			});
			
			// Start the microservice and keep the process running
			await beamConfigBuilder.RunForever();
		}
	}
}
