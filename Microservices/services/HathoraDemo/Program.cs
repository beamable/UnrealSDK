using Beamable.Server;
using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Threading.Tasks;

namespace Beamable.HathoraDemo
{
	public class Program
	{
		/// <summary>
		/// The entry point for the <see cref="HathoraDemo"/> service.
		/// </summary>
		public static async Task Main()
		{
			// inject data from the CLI
			await MicroserviceBootstrapper.Prepare<HathoraDemo>();
			
			// run the Microservice code
			await MicroserviceBootstrapper.Start<HathoraDemo>();
		}
	}
}
