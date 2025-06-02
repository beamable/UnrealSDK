using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Common.Content;
using Beamable.SuiFederation.Features.Accounts;
using Beamable.SuiFederation.Features.Content.FunctionMessages;
using Beamable.SuiFederation.Features.Content.Models;
using Beamable.SuiFederation.Features.Contract;
using Beamable.SuiFederation.Features.Contract.Storage.Models;
using Beamable.SuiFederation.Features.Inventory.Models;
using Beamable.SuiFederation.Features.Inventory.Storage;
using Beamable.SuiFederation.Features.Inventory.Storage.Models;
using Beamable.SuiFederation.Features.SuiApi;
using Beamable.SuiFederation.Features.SuiApi.Models;
using Beamable.SuiFederation.Features.Transactions;
using Beamable.SuiFederation.Features.Transactions.Storage.Models;
using SuiFederationCommon.Extensions;
using SuiFederationCommon.Models;

namespace Beamable.SuiFederation.Features.Content.Handlers;

public class NftHandler : IService, IContentHandler
{
    private readonly ContractService _contractService;
    private readonly SuiApiService _suiApiService;
    private readonly TransactionManagerFactory _transactionManagerFactory;
    private readonly MintCollection _mintCollection;
    private readonly AccountsService _accountsService;

    public NftHandler(ContractService contractService, SuiApiService suiApiService, TransactionManagerFactory transactionManagerFactory, MintCollection mintCollection, AccountsService accountsService)
    {
        _contractService = contractService;
        _suiApiService = suiApiService;
        _transactionManagerFactory = transactionManagerFactory;
        _mintCollection = mintCollection;
        _accountsService = accountsService;
    }

    public async Task<BaseMessage?> ConstructMessage(string transaction, string wallet, InventoryRequest inventoryRequest, IContentObject contentObject)
    {
        var contract = await _contractService.GetByContentId<NftContract>(inventoryRequest.ToNftType());
        var nftItem = NftContentItemExtensions.Create(inventoryRequest, (contentObject as INftBase)!);
        return new NftMintMessage(
            inventoryRequest.ContentId,
            contract.PackageId,
            contract.Module,
            "mint",
            wallet,
            contract.AdminCap,
            nftItem);
    }

    public async Task<BaseMessage?> ConstructMessage(string transaction, string wallet, InventoryRequestUpdate inventoryRequest,
        IContentObject contentObject)
    {
        var contract = await _contractService.GetByContentId<NftContract>(inventoryRequest.ToNftType());
        var playerAccount = await _accountsService.GetAccountByAddress(wallet);
        return new NftUpdateMessage(
            inventoryRequest.ContentId,
            contract.PackageId,
            contract.Module,
            "update",
            wallet,
            inventoryRequest.ProxyId,
            contract.OwnerInfo,
            playerAccount!.PrivateKey,
            inventoryRequest.Properties
                .Select(kvp => new NftAttribute(kvp.Key, kvp.Value))
                .ToArray()
        );
    }

    public async Task<BaseMessage?> ConstructMessage(string transaction, string wallet, InventoryRequestDelete inventoryRequest,
        IContentObject contentObject)
    {
        var contract = await _contractService.GetByContentId<NftContract>(inventoryRequest.ToNftType());
        var playerAccount = await _accountsService.GetAccountByAddress(wallet);
        return new NftDeleteMessage(
            inventoryRequest.ContentId,
            contract.PackageId,
            contract.Module,
            "burn",
            wallet,
            inventoryRequest.ProxyId,
            contract.OwnerInfo,
            playerAccount!.PrivateKey
        );
    }

    public async Task SendMessages(string transaction, List<BaseMessage> messages)
    {
        if (messages.Count == 0) return;

        var mintMessages = messages.OfType<NftMintMessage>().ToList();
        var updateMessages = messages.OfType<NftUpdateMessage>().ToList();
        var deleteMessages = messages.OfType<NftDeleteMessage>().ToList();

        if (mintMessages.Count > 0)
        {
            await SendMintMessages(transaction, mintMessages);
        }

        if (updateMessages.Count > 0)
        {
            await SendUpdateMessages(transaction, updateMessages);
        }

        if (deleteMessages.Count > 0)
        {
            await SendDeleteMessages(transaction, deleteMessages);
        }
    }

    private async Task SendDeleteMessages(string transaction, List<NftDeleteMessage> messages)
    {
        var transactionManager = _transactionManagerFactory.Create(transaction);
        try
        {
            var result = await _suiApiService.DeleteNft(messages);
            await transactionManager.AddChainTransaction(new ChainTransaction
            {
                Digest = result.digest,
                Error = result.error,
                Function = $"{nameof(NftHandler)}.{nameof(SendDeleteMessages)}",
                GasUsed = result.gasUsed,
                Data = messages.SerializeSelected(),
                Status = result.status,
            });
            if (result.status != "success")
            {
                var message = $"{nameof(NftHandler)}.{nameof(SendDeleteMessages)} failed with status {result.status}";
                BeamableLogger.LogError(message);
                await transactionManager.TransactionError(transaction, new Exception(message));
            }
        }
        catch (Exception e)
        {
            var message =
                $"{nameof(NftHandler)}.{nameof(SendDeleteMessages)} failed with error {e.Message}";
            BeamableLogger.LogError(message);
            await transactionManager.TransactionError(transaction, new Exception(message));
        }
    }

    private async Task SendUpdateMessages(string transaction, List<NftUpdateMessage> messages)
    {
        var transactionManager = _transactionManagerFactory.Create(transaction);
        try
        {
            var result = await _suiApiService.UpdateNft(messages);
            await transactionManager.AddChainTransaction(new ChainTransaction
            {
                Digest = result.digest,
                Error = result.error,
                Function = $"{nameof(NftHandler)}.{nameof(SendUpdateMessages)}",
                GasUsed = result.gasUsed,
                Data = messages.SerializeSelected(),
                Status = result.status,
            });
            if (result.status != "success")
            {
                var message = $"{nameof(NftHandler)}.{nameof(SendUpdateMessages)} failed with status {result.status}";
                BeamableLogger.LogError(message);
                await transactionManager.TransactionError(transaction, new Exception(message));
            }
        }
        catch (Exception e)
        {
            var message =
                $"{nameof(NftHandler)}.{nameof(SendUpdateMessages)} failed with error {e.Message}";
            BeamableLogger.LogError(message);
            await transactionManager.TransactionError(transaction, new Exception(message));
        }
    }

    public async Task SendMintMessages(string transaction, List<NftMintMessage> messages)
    {
        var transactionManager = _transactionManagerFactory.Create(transaction);
        try
        {
            var result = await _suiApiService.MintNfts(messages);
            await transactionManager.AddChainTransaction(new ChainTransaction
            {
                Digest = result.digest,
                Error = result.error,
                Function = $"{nameof(NftHandler)}.{nameof(SendMintMessages)}",
                GasUsed = result.gasUsed,
                Data = messages.SerializeSelected(),
                Status = result.status,
            });
            if (result.status != "success")
            {
                var message = $"{nameof(NftHandler)}.{nameof(SendMintMessages)} failed with status {result.status}";
                BeamableLogger.LogError(message);
                await transactionManager.TransactionError(transaction, new Exception(message));
            }
            else
            {
                await _mintCollection.InsertMints(
                    messages.Select(m => new Mint
                    {
                        PackageId = m.PackageId,
                        Module = m.Module,
                        Digest = result.digest,
                        ContentId = m.ContentId,
                        InitialOwnerAddress = m.PlayerWalletAddress,
                        Metadata = m.ToMetadata()
                    }));
            }
        }
        catch (Exception e)
        {
            var message =
                $"{nameof(NftHandler)}.{nameof(SendMintMessages)} failed with error {e.Message}";
            BeamableLogger.LogError(message);
            await transactionManager.TransactionError(transaction, new Exception(message));
        }
    }

    public async Task<IFederatedState> GetState(string wallet, string contentId)
    {
        var contentTypePart = contentId.ToContentType();
        var contract = await _contractService.GetByContentId<NftContract>(contentTypePart);
        var ownedObjects = await _suiApiService.GetOwnedObjects(wallet, new GetOwnedObjectsRequest(contract.PackageId));
        return new ItemsState
        {
            Items = ownedObjects.ToInventoryState()
        };
    }
}