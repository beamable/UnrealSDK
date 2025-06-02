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

namespace Beamable.SuiFederation.Features.Content.Handlers;

public class RegularCoinHandler : IService, IContentHandler
{
    private readonly ContractService _contractService;
    private readonly SuiApiService _suiApiService;
    private readonly TransactionManagerFactory _transactionManagerFactory;
    private readonly MintCollection _mintCollection;
    private readonly AccountsService _accountsService;

    public RegularCoinHandler(ContractService contractService, SuiApiService suiApiService, TransactionManagerFactory transactionManagerFactory, MintCollection mintCollection, AccountsService accountsService)
    {
        _contractService = contractService;
        _suiApiService = suiApiService;
        _transactionManagerFactory = transactionManagerFactory;
        _mintCollection = mintCollection;
        _accountsService = accountsService;
    }

    public async  Task<BaseMessage?> ConstructMessage(string transaction, string wallet, InventoryRequest inventoryRequest, IContentObject contentObject) =>
        inventoryRequest.Amount switch
        {
            > 0 => await PositiveAmountMessage(transaction, wallet, "mint", inventoryRequest),
            < 0 => await NegativeAmountMessage(transaction, wallet, "burn", inventoryRequest),
            _ => null
        };

    public Task<BaseMessage?> ConstructMessage(string transaction, string wallet, InventoryRequestUpdate inventoryRequest,
        IContentObject contentObject)
    {
        return Task.FromResult<BaseMessage?>(EmptyMessageExtensions.Create());
    }

    public Task<BaseMessage?> ConstructMessage(string transaction, string wallet, InventoryRequestDelete inventoryRequest,
        IContentObject contentObject)
    {
        return Task.FromResult<BaseMessage?>(EmptyMessageExtensions.Create());
    }

    private async Task<RegularCoinMintMessage> PositiveAmountMessage(string transaction, string wallet, string function, InventoryRequest inventoryRequest)
    {
        var contract = await _contractService.GetByContentId<CoinContract>(inventoryRequest.ContentId);
        return new RegularCoinMintMessage(
            inventoryRequest.ContentId,
            contract.PackageId,
            contract.Module,
            function,
            wallet,
            contract.AdminCap,
            contract.TreasuryCap,
            inventoryRequest.Amount);
    }

    private async Task<RegularCoinBurnMessage?> NegativeAmountMessage(string transaction, string wallet, string function, InventoryRequest inventoryRequest)
    {
        var transactionManager = _transactionManagerFactory.Create(transaction);
        var contract = await _contractService.GetByContentId<CoinContract>(inventoryRequest.ContentId);
        var playerAccount = await _accountsService.GetAccountByAddress(wallet);
        var balance = await _suiApiService.GetCoinBalance(wallet, new CoinBalanceRequest(contract.PackageId, contract.Module));
        if (balance.Total >= Math.Abs(inventoryRequest.Amount))
            return new RegularCoinBurnMessage(
                inventoryRequest.ContentId,
                contract.PackageId,
                contract.Module,
                function,
                wallet,
                contract.TreasuryCap,
                Math.Abs(inventoryRequest.Amount),
                playerAccount!.PrivateKey
                );

        await transactionManager.AddChainTransaction(new ChainTransaction
        {
            Error = $"Insufficient funds for {inventoryRequest.ContentId}, balance is {balance.Total}, requested is {Math.Abs(inventoryRequest.Amount)}",
            Function = $"{nameof(RegularCoinHandler)}.{nameof(NegativeAmountMessage)}",
            Status = "rejected",
        });
        return null;
    }

    public async Task SendMessages(string transaction, List<BaseMessage> messages)
    {
        if (messages.Count == 0) return;

        var mintMessages = messages.OfType<RegularCoinMintMessage>().ToList();
        var burnMessages = messages.OfType<RegularCoinBurnMessage>().ToList();

        if (mintMessages.Count > 0)
        {
            await SendPositiveAmountMessage(transaction, mintMessages);
        }

        if (burnMessages.Count > 0)
        {
            await SendNegativeMessage(transaction, burnMessages);
        }
    }

    private async Task SendPositiveAmountMessage(string transaction, List<RegularCoinMintMessage> messages)
    {
        var transactionManager = _transactionManagerFactory.Create(transaction);
        try
        {
            var result = await _suiApiService.MintRegularCurrency(messages);
            await transactionManager.AddChainTransaction(new ChainTransaction
            {
                Digest = result.digest,
                Error = result.error,
                Function = $"{nameof(RegularCoinHandler)}.{nameof(SendPositiveAmountMessage)}",
                GasUsed = result.gasUsed,
                Data = messages.SerializeSelected(),
                Status = result.status,
            });
            if (result.status != "success")
            {
                var message = $"{nameof(RegularCoinHandler)}.{nameof(SendPositiveAmountMessage)} failed with status {result.status}";
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
                $"{nameof(RegularCoinHandler)}.{nameof(SendPositiveAmountMessage)} failed with error {e.Message}";
            BeamableLogger.LogError(message);
            await transactionManager.TransactionError(transaction, new Exception(message));
        }
    }

    private async Task SendNegativeMessage(string transaction, List<RegularCoinBurnMessage> messages)
    {
        var transactionManager = _transactionManagerFactory.Create(transaction);
        try
        {
            var result = await _suiApiService.BurnRegularCurrency(messages);
            await transactionManager.AddChainTransaction(new ChainTransaction
            {
                Digest = result.digest,
                Error = result.error,
                Function = $"{nameof(RegularCoinHandler)}.{nameof(SendNegativeMessage)}",
                GasUsed = result.gasUsed,
                Data = messages.SerializeSelected(),
                Status = result.status,
            });
            if (result.status != "success")
            {
                var message = $"{nameof(RegularCoinHandler)}.{nameof(SendNegativeMessage)} failed with status {result.status}";
                BeamableLogger.LogError(message);
                await transactionManager.TransactionError(transaction, new Exception(message));
            }
        }
        catch (Exception e)
        {
            var message =
                $"{nameof(RegularCoinHandler)}.{nameof(SendNegativeMessage)} failed with error {e.Message}";
            BeamableLogger.LogError(message);
            await transactionManager.TransactionError(transaction, new Exception(message));
        }
    }

    public async Task<IFederatedState> GetState(string wallet, string contentId)
    {
        var contract = await _contractService.GetByContentId<CoinContract>(contentId);
        var balance = await _suiApiService.GetCoinBalance(wallet, new CoinBalanceRequest(contract.PackageId, contract.Module));
        return new CurrenciesState
        {
            Currencies = new Dictionary<string, long>
            {
                { contentId, balance.Total }
            }
        };
    }
}