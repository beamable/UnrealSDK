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
			// inject data from the CLI.
			await MicroserviceBootstrapper.Prepare<BeamballMs>();
			
			// run the Microservice code
			await MicroserviceBootstrapper.Start<BeamballMs>();
		}
	}
}
