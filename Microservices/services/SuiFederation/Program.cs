using System;
using System.Reflection;
using Beamable.Server;
using System.Threading.Tasks;
using Beamable.SuiFederation.Features.Transactions;
using SuiFederationCommon;

namespace Beamable.SuiFederation
{
	public class Program
	{
		/// <summary>
		/// The entry point for the <see cref="SuiFederation"/> service.
		/// </summary>
		public static async Task Main()
		{
			//Preload content types from Common project
			AppDomain.CurrentDomain.Load(Assembly.GetAssembly(typeof(SuiFederationCommonAssemblyIdentifier))!.GetName());

			// Registering in-flight transaction shutdown hook.
			TransactionManager.SetupShutdownHook();

			// inject data from the CLI.
			await MicroserviceBootstrapper.Prepare<SuiFederation>();
			
			// run the Microservice code
			await MicroserviceBootstrapper.Start<SuiFederation>();
		}
	}
}