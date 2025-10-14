using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.SuiFederation.Features.Accounts;
using Beamable.SuiFederation.Features.Accounts.Models;
using Beamable.SuiFederation.Features.Accounts.Storage.Models;
using Beamable.SuiFederation.Features.LockManager;
using Beamable.SuiFederation.Features.SuiApi;
using Beamable.SuiFederation.Features.SuiApi.Models;
using Beamable.SuiFederation.Features.Transactions;
using Beamable.SuiFederation.Features.Transactions.Storage.Models;
using Beamable.SuiFederation.Features.WalletManager.Exceptions;
using Beamable.SuiFederation.Features.WalletManager.Models;

namespace Beamable.SuiFederation.Features.WalletManager;

public class WalletManagerService : IService
{
    private readonly Configuration _configuration;
    private readonly AccountsService _accountsService;
    private readonly LockManagerService _lockManagerService;
    private readonly SuiApiService _suiApiService;

    public WalletManagerService(Configuration configuration, AccountsService accountsService, LockManagerService lockManagerService, SuiApiService suiApiService)
    {
        _configuration = configuration;
        _accountsService = accountsService;
        _lockManagerService = lockManagerService;
        _suiApiService = suiApiService;
    }

    private const string WorkingAccountNamePrefix = "working-account";
    private const int LockIterationAttempts = 10;
    private const int LockDelayBetweenAttemptsMs = 100;

    public async Task<Account> GetWorkingWallet(TransactionManager transactionManager, SuiLockRequest request = default)
    {
        try
        {
            request = request == default ? SuiLockRequest.Default() : request;
            var workingAccount = await GetWorkingWalletInternal(request);
            var workingBalance = await GetWalletBalance(workingAccount.Address, request.CoinPackage, request.CoinModule);
            await DistributeCoins(request, workingBalance, workingAccount, transactionManager);
            return workingAccount;
        }
        finally
        {
            await ReleaseWallet(AccountsService.RealmAccountName);
        }
    }

    public async Task ReleaseWallet(string walletName)
    {
        await _lockManagerService.ReleaseLock(walletName);
    }

    private async Task DistributeCoins(SuiLockRequest request, WalletCoinBalance walletCoinBalance, Account workingAccount, TransactionManager transactionManager)
    {
        if (walletCoinBalance.Balance >= await _configuration.SuiCoinMinimalAmountMist
            && walletCoinBalance.Balance >= request.Amount) return;

        var realmAccount = await _accountsService.GetOrCreateRealmAccount();
        var realmWalletBalance = await GetWalletBalance(realmAccount.Address, request.CoinPackage, request.CoinModule);
        if (realmWalletBalance.Balance < request.Amount || realmWalletBalance.Balance <= await _configuration.SuiCoinMinimalAmountMist)
            throw new RealmAccountBalanceException("Realm wallet has insufficient coin balance.");

        await TransferCoins(request, walletCoinBalance, realmAccount, realmWalletBalance, workingAccount, transactionManager);
    }

    private async Task TransferCoins(SuiLockRequest request, WalletCoinBalance walletCoinBalance, Account realmAccount, WalletCoinBalance realmWalletBalance, Account workingAccount, TransactionManager transactionManager)
    {
        if (walletCoinBalance.Balance > await _configuration.SuiCoinMinimalAmountMist)
            return;
        var iterations = 0;
        while (iterations < LockIterationAttempts)
        {
            var realmLocked = await _lockManagerService.AcquireLock(AccountsService.RealmAccountName);
            if (realmLocked)
            {
                var transferAmount = await CalculateSuiTransferAmount(realmWalletBalance);
                var result = await _suiApiService.TransferSui(walletCoinBalance.Wallet, transferAmount);
                await transactionManager.AddChainTransaction(new ChainTransaction
                {
                    Digest = result.digest,
                    Error = result.error,
                    Function = $"{nameof(WalletManagerService)}.{nameof(TransferCoins)}",
                    GasUsed = result.gasUsed,
                    Data = JsonSerializer.Serialize(request),
                    Status = result.status,
                });
                if (result.IsSuccess)
                {
                    await _accountsService.SetCoinBalance(workingAccount.Name, request.CoinModule,walletCoinBalance.Balance + transferAmount);
                }
                else
                {
                    var message = $"{nameof(WalletManagerService)}.{nameof(TransferCoins)} failed with status {result.status}";
                    BeamableLogger.LogError(message);
                }
                await _lockManagerService.ReleaseLock(AccountsService.RealmAccountName);
                return;
            }
            await Task.Delay(LockDelayBetweenAttemptsMs);
            iterations++;
        }
    }

    private async ValueTask<long> CalculateSuiTransferAmount(WalletCoinBalance realmWalletBalance)
    {
        var equalSplit = WalletManagerExtensions.SafeDivide(realmWalletBalance.Balance, await _configuration.NumberOfWorkingWallets);
        if (equalSplit <= 0)
            return await _configuration.SuiCoinMinimalAmountMist;
        var percentageOfEqual = equalSplit * await _configuration.CoinTransferPercentage / 100;
        if (realmWalletBalance.Balance >= percentageOfEqual)
            return percentageOfEqual;
        return await _configuration.SuiCoinMinimalAmountMist;
    }

    private async Task<WalletCoinBalance> GetWalletBalance(string wallet, string coinPackage, string coinModule)
    {
        try
        {
            var walletBalance = await _suiApiService.GetCoinBalance(wallet, new CoinBalanceRequest(coinPackage, coinModule));
            return new WalletCoinBalance
            {
                Wallet = wallet,
                Balance = walletBalance.Total
            };
        }
        catch (Exception e)
        {
            BeamableLogger.LogWarning($"Unable to get balance for wallet {wallet} with exception {e.Message}");
            return new WalletCoinBalance(wallet,0);
        }
    }

    private async Task<Account> GetWorkingWalletInternal(SuiLockRequest request)
    {
        try
        {
            var lockedWallet = await TryLockWorkingWalletAccount(request);
            return lockedWallet ?? await CreateNewAndLock();
        }
        catch (MaxNumberOfWorkingWallets)
        {
            throw;
        }
        catch (Exception)
        {
            throw new NoWorkingWalletsException();
        }
    }

    private async Task<Account> CreateNewAndLock()
    {
        if (await _configuration.NumberOfWorkingWallets > await _configuration.MaxNumberOffWorkingWallets)
            throw new MaxNumberOfWorkingWallets();
        var nextWorkingWallet = await _configuration.NumberOfWorkingWallets + 1;
        var newWalletName = $"{WorkingAccountNamePrefix}-{nextWorkingWallet}";
        BeamableLogger.Log($"Creating new working wallet {newWalletName}.");
        await _lockManagerService.AcquireLock(newWalletName);
        await _configuration.Update(nameof(_configuration.NumberOfWorkingWallets), $"{nextWorkingWallet}");
        return await _accountsService.GetOrCreateAccount(newWalletName);
    }

    private async Task<Account?> TryLockWorkingWalletAccount(SuiLockRequest request)
    {
        var iterations = await _configuration.NumberOfWorkingWallets;
        while (iterations > 0)
        {
            var lockedWallets = await _lockManagerService.GetLocked();
            var existingWorkingAccounts = await _accountsService.GetVaultsByPrefixAndBalance(WorkingAccountNamePrefix, request.CoinModule, request.Amount);
            var randomList = await DetermineRandomList(existingWorkingAccounts, lockedWallets.Select(s => int.Parse(s.Split('-').Last())).ToList());
            foreach (var random in randomList)
            {
                var workingWallet = $"{WorkingAccountNamePrefix}-{random}";
                var lockAcquired = await _lockManagerService.AcquireLock(workingWallet);
                if (lockAcquired) return await _accountsService.GetOrCreateAccount(workingWallet);
            }
            await Task.Delay(LockDelayBetweenAttemptsMs);
            iterations--;
        }
        BeamableLogger.LogWarning("Can't find free working wallet.");
        return null;
    }

    private async ValueTask<IEnumerable<int>> DetermineRandomList(IEnumerable<Vault> existingWorkingAccounts, List<int> lockedWallets)
    {
        var randomList = WalletManagerExtensions.GenerateRandomList(await _configuration.NumberOfWorkingWallets, lockedWallets);
        var existingWallets = existingWorkingAccounts.Select(s => int.Parse(s.Name.Split('-').Last())).ToList();
        WalletManagerExtensions.ShuffleList(existingWallets);
        var reorderedList = new List<int>();
        reorderedList.AddRange(existingWallets);
        var additionalSet = new HashSet<int>(existingWallets);
        reorderedList.AddRange(randomList.Where(number => !additionalSet.Contains(number)));
        return reorderedList;
    }
}