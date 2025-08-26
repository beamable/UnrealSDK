using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Common.Api.Auth;
using Beamable.Common.Content;
using Beamable.Common.Inventory;
using Beamable.Server;
using Beamable.SuiFederation.Features.LockManager;
using Beamable.Server.Content;
using Beamable.SuiFederation.Caching;
using Beamable.SuiFederation.Extensions;
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
    private readonly MemoryCache<List<IContentObject>> _contentCache = new(TimeSpan.FromDays(1));

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
#if !DEBUG
        socketRequesterContext.Subscribe<object>(Constants.Features.Services.CONTENT_UPDATE_EVENT, _ =>
        {
            Task.Run(async () =>
            {
                try
                {
                    BeamableLogger.Log("Content was updated");
                    _contentCache.RemoveAll();
                    await InitializeContentContracts();
                }
                catch (Exception ex)
                {
                    BeamableLogger.LogError($"Error during content update: {ex}");
                }
            });
        });
#endif
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

    public async Task<IEnumerable<IContentObject>> FetchFederationContentForState(ExternalIdentity externalIdentity)
    {
        var federationContent = await FetchFederationContentLocal();
        var currencies = federationContent
            .Where(item => item is CurrencyContent coin && coin.federation.Matches(externalIdentity));

        var groupsByPath = federationContent
            .Where(item => item is ItemContent)
            .GroupBy(item => {
                var idParts = item.Id.Split('.');
                return string.Join(".", idParts.Take(idParts.Length - 1));
            })
            .ToDictionary(g => g.Key, g => g.ToList());

        var matchingItems = groupsByPath
            .Select(kvp => kvp.Value.FirstOrDefault(co => co is ItemContent item && item.federation.Matches(externalIdentity)))
            .Where(co => co is not null)
            .Cast<IContentObject>();
        return matchingItems.Concat(currencies);
    }

    private async Task<List<IContentObject>> FetchFederationContentLocal()
    {
        return await _contentCache.GetOrAddAsync(nameof(FetchFederationContentLocal), async () =>
        {
            var federatedTypes = SuiFederationCommonHelper.GetFederationTypes();
            var manifest = await _contentService.GetManifest(new ContentQuery
            {
                TypeConstraints = federatedTypes
            });

            var result = new List<IContentObject>();
            foreach (var clientContentInfo in manifest.entries.Where(
                         item => item.contentId.StartsWith("currency") ||
                                 item.contentId.StartsWith("items")))
            {
                var contentRef = await clientContentInfo.Resolve();
                result.Add(contentRef);
            }
            return result;
        }) ?? new List<IContentObject>();
    }
}