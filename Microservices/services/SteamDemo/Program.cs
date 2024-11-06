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
			// inject data from the CLI.
			await MicroserviceBootstrapper.Prepare<SteamDemo>();
			
			// run the Microservice code
			await MicroserviceBootstrapper.Start<SteamDemo>();
		}
	}
}
