using Beamable.Server;
using System.Threading.Tasks;

namespace Beamable.LiveOpsDemoMs
{
	public class Program
	{
		/// <summary>
		/// The entry point for the <see cref="LiveOpsDemoMs"/> service.
		/// </summary>
		public static async Task Main()
		{
			// inject data from the CLI.
			await MicroserviceBootstrapper.Prepare<LiveOpsDemoMs>();
			
			// run the Microservice code
			await MicroserviceBootstrapper.Start<LiveOpsDemoMs>();
		}
	}
}
