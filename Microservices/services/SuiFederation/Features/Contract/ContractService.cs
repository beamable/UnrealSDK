using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Common.Content;
using Beamable.Server;
using Beamable.SuiFederation.Features.LockManager;
using Beamable.Server.Content;
using Beamable.SuiFederation.Features.Contract.Exceptions;
using Beamable.SuiFederation.Features.Contract.Handlers;
using Beamable.SuiFederation.Features.Contract.Storage;
using Beamable.SuiFederation.Features.Contract.Storage.Models;
using Beamable.SuiFederation.Features.Contract.SuiClientWrapper;
using SuiFederationCommon;

namespace Beamable.SuiFederation.Features.Contract;

public class ContractService : IService
{
    private readonly LockManagerService _lockManagerService;
    private readonly ContentService _contentService;
    private readonly ContentContractHandlerResolver _contractHandlerResolver;
    private readonly ContractCollection _contractCollection;
    private readonly SuiClient _suiClient;

    public ContractService(SocketRequesterContext socketRequesterContext, LockManagerService lockManagerService, ContentService contentService, ContentContractHandlerResolver contentContractHandlerResolver, ContractCollection contractCollection, SuiClient suiClient)
    {
        _lockManagerService = lockManagerService;
        _contentService = contentService;
        _contractHandlerResolver = contentContractHandlerResolver;
        _contractCollection = contractCollection;
        _suiClient = suiClient;
        SubscribeContentUpdateEvent(socketRequesterContext);
    }

    private void SubscribeContentUpdateEvent(SocketRequesterContext socketRequesterContext)
    {
        socketRequesterContext.Subscribe<object>(Constants.Features.Services.CONTENT_UPDATE_EVENT, _ =>
        {
            Task.Run(async () =>
            {
                try
                {
                    BeamableLogger.Log("Content was updated");
                    await InitializeContentContracts();
                }
                catch (Exception ex)
                {
                    BeamableLogger.LogError($"Error during content update: {ex}");
                }
            });
        });
    }

    public async Task InitializeContentContracts()
    {
        const string lockName = "initializeContracts";
        try
        {
            _ = Extensions.TaskExtensions.RunAsyncBlock(async () =>
            {
                if (!await _lockManagerService.AcquireLock(lockName)) return;

                await _suiClient.Initialize();

                await foreach (var contentObject in FetchFederationContent())
                {
                    await _contractHandlerResolver.HandleContent(contentObject);
                }
            });
        }
        finally
        {
            await _lockManagerService.ReleaseLock(lockName);
        }
    }

    public async Task<TContract> GetByContentId<TContract>(string contentId) where TContract : ContractBase
    {
        var contract = await _contractCollection.GetByContentId<TContract>(contentId);
        if (contract is null)
            throw new ContractException($"Contract for {contentId} don't exist.");
        return contract;
    }

    public async Task<TContract?> GetByContent<TContract>(string contentId) where TContract : ContractBase
    {
        return await _contractCollection.GetByContentId<TContract>(contentId);
    }

    public async Task<bool> ContractExists<TContract>(string contentId) where TContract : ContractBase
    {
        return await _contractCollection.GetByContentId<TContract>(contentId) != null;
    }

    public async Task<bool> InsertContract<TContract>(TContract contract) where TContract : ContractBase
    {
        return await _contractCollection.TryInsert(contract);
    }

    public async Task<bool> UpsertContract<TContract>(TContract contract, string id) where TContract : ContractBase
    {
        return await _contractCollection.TryUpsert(contract, id);
    }

    public async IAsyncEnumerable<IContentObject> FetchFederationContent()
    {
        var federatedTypes = SuiFederationCommonHelper.GetFederationTypes();
        var manifest = await _contentService.GetManifest(new ContentQuery
        {
            TypeConstraints = federatedTypes
        });

        var currencyItems = manifest.entries.Where(item => item.contentId.StartsWith("currency")).ToList();

        var groupedWeaponItems = manifest.entries
            .Where(item => item.contentId.StartsWith("items"))
            .GroupBy(item => item.contentId.Split('.')[1]) // Group by the second word (e.g., "weapon")
            .Select(group => group.First()) // Take the first item from each group
            .ToList();

        var filtered = currencyItems.Concat(groupedWeaponItems).ToList();

        foreach (var clientContentInfo in filtered)
        {
            var contentRef = await clientContentInfo.Resolve();
            yield return contentRef;
        }
    }
}