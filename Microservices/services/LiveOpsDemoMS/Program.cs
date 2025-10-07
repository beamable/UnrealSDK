using Beamable.Server;
using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Threading.Tasks;

namespace Beamable.LiveOpsDemoMS
{
	public class Program
	{
		/// <summary>
		/// The entry point for the <see cref="LiveOpsDemoMS"/> service.
		/// </summary>
		public static async Task Main()
		{
			// Creating the builder that we use to setup the config of microservice
			var beamConfigBuilder = BeamServer.Create();

			beamConfigBuilder.IncludeRoutes<LiveOpsDemoMS>(routePrefix: "");
			
			// Start the microservice and keep the process running
			await beamConfigBuilder.RunForever();
		}
	}
}
