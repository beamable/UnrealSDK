using System;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Server;
using Beamable.SuiFederation.Features.Accounts;
using Beamable.SuiFederation.Features.Accounts.Exceptions;
using Beamable.SuiFederation.Features.Content.FunctionMessages;
using Beamable.SuiFederation.Features.Contract;
using Beamable.SuiFederation.Features.Contract.Storage.Models;
using Beamable.SuiFederation.Features.SuiApi;
using Beamable.SuiFederation.Features.SuiApi.Models;
using Beamable.SuiFederation.Features.Transactions;
using Beamable.SuiFederation.Features.Transactions.Storage.Models;
using Beamable.SuiFederation.Features.Withdrawal.Exceptions;

namespace Beamable.SuiFederation.Features.Withdrawal;

public class WithdrawalService : IService
{
    private readonly AccountsService _accountsService;
    private readonly SuiApiService _suiApiService;
    private readonly ContractService _contractService;
    private readonly TransactionManagerFactory _transactionManagerFactory;

    public WithdrawalService(AccountsService accountsService, SuiApiService suiApiService, ContractService contractService, TransactionManagerFactory transactionManagerFactory)
    {
        _accountsService = accountsService;
        _suiApiService = suiApiService;
        _contractService = contractService;
        _transactionManagerFactory = transactionManagerFactory;
    }

    public async Task<GameCoinTransferMessage> Initialize(long gamerTag, string toAddress, string contentId, long amount)
    {
        var playerAccount = await _accountsService.GetAccount(gamerTag.ToString());
        if (playerAccount is null)
            throw new UnknownAccountException($"External identity doesn't exist");

        var contract = await _contractService.GetByContentId<ContractBase>(contentId);
        if (contract is not CoinContract)
            throw new WithdrawalException($"Content {contentId} does not allow transfers");
        var balance = await _suiApiService.GetCoinBalance(playerAccount.Address, new CoinBalanceRequest(contract.PackageId, contract.Module));
        if (balance.Total < amount)
            throw new WithdrawalException($"Player {gamerTag} has not enough coins for this withdrawal");

        return new GameCoinTransferMessage(contentId, contract.PackageId, contract.Module, "transfer", playerAccount.Address, playerAccount.PrivateKey, gamerTag, toAddress, amount);
    }

    public async Task Withdraw(string transaction, GameCoinTransferMessage request)
    {
        var transactionManager = _transactionManagerFactory.Create(transaction);
        try
        {
            var result = await _suiApiService.WithdrawCurrency(request);
            await transactionManager.AddChainTransaction(new ChainTransaction
            {
                Digest = result.digest,
                Error = result.error,
                Function = $"{nameof(WithdrawalService)}.{nameof(Withdraw)}",
                GasUsed = result.gasUsed,
                Data = request.SerializeSelected(),
                Status = result.status,
            });
            if (result.status != "success")
            {
                var message = $"{nameof(WithdrawalService)}.{nameof(Withdraw)} failed with status {result.status}";
                BeamableLogger.LogError(message);
                await transactionManager.TransactionError(transaction, new Exception(message));
            }
        }
        catch (Exception e)
        {
            var message =
                $"{nameof(WithdrawalService)}.{nameof(Withdraw)} failed with error {e.Message}";
            BeamableLogger.LogError(message);
            await transactionManager.TransactionError(transaction, new Exception(message));
        }
    }
}