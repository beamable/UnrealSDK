using Beamable.Server;
using System.Threading.Tasks;

namespace Beamable.DiscordSampleMs
{
	public class Program
	{
		/// <summary>
		/// The entry point for the <see cref="DiscordSampleMs"/> service.
		/// </summary>
		public static async Task Main()
		{
			// inject data from the CLI.
			await MicroserviceBootstrapper.Prepare<DiscordSampleMs>();
			
			// run the Microservice code
			await MicroserviceBootstrapper.Start<DiscordSampleMs>();
		}
	}
}
