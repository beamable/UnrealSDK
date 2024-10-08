using Beamable.Server;
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
			// inject data from the CLI.
			await MicroserviceBootstrapper.Prepare<LiveOpsDemoMS>();
			
			// run the Microservice code
			await MicroserviceBootstrapper.Start<LiveOpsDemoMS>();
		}
	}
}
