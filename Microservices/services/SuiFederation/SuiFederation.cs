using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Common.Api.Inventory;
using Beamable.Server;
using Beamable.SuiFederation.Endpoints;
using Beamable.SuiFederation.Extensions;
using Beamable.SuiFederation.Features.Accounts;
using Beamable.SuiFederation.Features.ChannelProcessor;
using SuiFederationCommon;

namespace Beamable.SuiFederation
{
	[Microservice(SuiFederationSettings.MicroserviceName)]
	public partial class SuiFederation : Microservice, IFederatedInventory<SuiWeb3Identity>
	{
		[ConfigureServices]
		public static void Configure(IServiceBuilder serviceBuilder)
		{
			var dependencyBuilder = serviceBuilder.Builder;
			dependencyBuilder.AddFeatures();
			dependencyBuilder.AddEndpoints();
		}

		[InitializeServices]
		public static async Task Initialize(IServiceInitializer initializer)
		{
			try
			{
				initializer.SetupExtensions();

				// Validate configuration
				if (string.IsNullOrWhiteSpace(await initializer.Provider.GetService<Configuration>().SuiEnvironment))
				{
					throw new ConfigurationException($"{nameof(Configuration.SuiEnvironment)} is not defined in realm config. Please apply the configuration and restart the service to make it operational.");
				}

				//Generate Realm account
				await initializer.Provider.GetService<AccountsService>().GetOrCreateRealmAccount();

#if !DEBUG
				await initializer.GetService<Features.Contract.ContractService>().InitializeContentContracts();
#endif
				//Start ChannelService queue processor
				ChannelService.Start();
			}
			catch (Exception ex)
			{
				BeamableLogger.LogException(ex);
				BeamableLogger.LogError("Service initialization failed. Fix the issues before using the service.");
			}
		}

		[AdminOnlyCallable(flags:CallableFlags.SkipGenerateClientFiles)]
		public async Promise<string> GetRealmAccount()
		{
			var account = await Provider.GetService<AccountsService>()
				.GetRealmAccount();
			return account?.Address ?? "";
		}

		[AdminOnlyCallable(flags:CallableFlags.SkipGenerateClientFiles)]
		public async Promise<string> GenerateRealmAccount()
		{
			var account = await Provider.GetService<AccountsService>()
				.GetOrCreateRealmAccount();
			return account.Address;
		}

		[AdminOnlyCallable(flags:CallableFlags.SkipGenerateClientFiles)]
		public async Promise<string> ImportRealmAccount(string privateKey)
		{
			var account = await Provider.GetService<AccountsService>()
				.GetOrImportRealmAccount(privateKey);
			return account.Address;
		}

		[AdminOnlyCallable(flags:CallableFlags.SkipGenerateClientFiles)]
		public async Promise<string> ImportAccount(string id, string privateKey)
		{
			var account = await Provider.GetService<AccountsService>()
				.ImportAccount(id, privateKey);
			return account.Address;
		}

		[AdminOnlyCallable(flags:CallableFlags.SkipGenerateClientFiles)]
		public async Promise<string> InitializeContentContracts()
		{
#if !DEBUG
			await Provider.GetService<Features.Contract.ContractService>().InitializeContentContracts();
			return "Contract initialization started..";
#else
			return await Task.FromResult($"Use {nameof(InitializeContentContracts)} only in Docker by running: dotnet beam services run --ids {SuiFederationSettings.MicroserviceName}");
#endif
		}

		async Promise<FederatedAuthenticationResponse> IFederatedLogin<SuiWeb3Identity>.Authenticate(string token, string challenge, string solution)
		{
			return await Provider.GetService<AuthenticateEndpoint>()
				.Authenticate(token, challenge, solution);
		}

		async Promise<FederatedInventoryProxyState> IFederatedInventory<SuiWeb3Identity>.GetInventoryState(string id)
		{
			var microserviceInfo = MicroserviceMetadataExtensions.GetMetadata<SuiFederation, SuiWeb3Identity>();
			var existingExternalIdentity = microserviceInfo.ToExternalIdentity();
			return await Provider.GetService<GetInventoryStateEndpoint>()
				.GetInventoryState(id, existingExternalIdentity);
		}

		async Promise<FederatedInventoryProxyState> IFederatedInventory<SuiWeb3Identity>.StartInventoryTransaction(string id, string transaction, Dictionary<string, long> currencies, List<FederatedItemCreateRequest> newItems, List<FederatedItemDeleteRequest> deleteItems,
			List<FederatedItemUpdateRequest> updateItems)
		{
			var gamerTag = await Provider.GetService<AccountsService>().GetGamerTag(id);
			var microserviceInfo = MicroserviceMetadataExtensions.GetMetadata<SuiFederation, SuiWeb3Identity>();
			return await Provider.GetService<StartInventoryTransactionEndpoint>()
				.StartInventoryTransaction(id, transaction, currencies, newItems, deleteItems, updateItems, gamerTag, microserviceInfo);
		}

		[Callable]
		public async Promise<string> GetSuiEnvironment()
		{
			return await Provider.GetService<Configuration>()
				.SuiEnvironment;
		}

		[ClientCallable]
		public async Promise Withdraw(string contentId, long amount)
		{
			await Provider.GetService<WithdrawalEndpoint>().Withdraw(contentId, amount);
		}
	}
}