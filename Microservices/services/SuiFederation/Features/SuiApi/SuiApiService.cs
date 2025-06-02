using System;
using System.Collections.Generic;
using System.Text.Json;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.SuiFederation.Features.Accounts;
using Beamable.SuiFederation.Features.Common;
using Beamable.SuiFederation.Features.Content.FunctionMessages;
using Beamable.SuiFederation.Features.Contract.FunctionMesseges;
using Beamable.SuiFederation.Features.SuiApi.Exceptions;
using Beamable.SuiFederation.Features.SuiApi.Models;
using SuiNodeServicve;

namespace Beamable.SuiFederation.Features.SuiApi;

public class SuiApiService : IService
{
    private readonly Configuration _configuration;
    private readonly AccountsService _accountsService;

    public SuiApiService(Configuration configuration, AccountsService accountsService)
    {
        _configuration = configuration;
        _accountsService = accountsService;
    }

    public static async Task<CreateWalletResponse> CreateWallet()
    {
        using (new Measure($"Sui.createWallet"))
        {
            try
            {
                var jsonString = await NodeService.CreateWallet();
                if (string.IsNullOrWhiteSpace(jsonString))
                    throw new Exception("createWallet output is empty.");

                return JsonSerializer.Deserialize<CreateWalletResponse>(jsonString)
                       ?? throw new Exception();
            }
            catch (JsonException ex)
            {
                BeamableLogger.LogError("Can't deserialize createWallet return. Error: {error}", ex.Message);
                throw new SuiApiException($"createWallet: {ex.Message}");
            }
            catch (Exception ex)
            {
                BeamableLogger.LogError("Can't generate new private key. Error: {error}", ex.Message);
                throw new SuiApiException($"createWallet: {ex.Message}");
            }
        }
    }

    public static async Task<CreateWalletResponse> ImportPrivateKey(string privateKey)
    {
        using (new Measure($"Sui.importWallet"))
        {
            try
            {
                var jsonString = await NodeService.ImportWallet(privateKey);

                if (string.IsNullOrWhiteSpace(jsonString))
                    throw new Exception("importWallet output is empty.");

                return JsonSerializer.Deserialize<CreateWalletResponse>(jsonString)
                       ?? throw new Exception();
            }
            catch (JsonException ex)
            {
                BeamableLogger.LogError("Can't deserialize importWallet return. Error: {error}", ex.Message);
                throw new SuiApiException($"importWallet: {ex.Message}");
            }
            catch (Exception ex)
            {
                BeamableLogger.LogError("Can't import a private key. Error: {error}", ex.Message);
                throw new SuiApiException($"importWallet: {ex.Message}");
            }
        }
    }

    public static async Task<bool> VerifySignature(string token, string challenge, string solution)
    {
        using (new Measure($"Sui.verifySignature: {token}"))
        {
            try
            {
                return await NodeService.VerifySignature(token, challenge, solution);
            }
            catch (Exception ex)
            {
                BeamableLogger.LogError("Can't verify signature for {token}. Error: {error}", token, ex.Message);
                return false;
            }
        }
    }

    public async Task<SuiTransactionResult> MintRegularCurrency(List<RegularCoinMintMessage> mintMessages)
    {
        using (new Measure($"Sui.MintRegularCurrency"))
        {
            try
            {
                var environment = await _configuration.SuiEnvironment;
                var realmAccount = await _accountsService.GetOrCreateRealmAccount();
                var mintRequestJson = JsonSerializer.Serialize(mintMessages);
                var result = await NodeService.MintRegularCoin(mintRequestJson, realmAccount.PrivateKey, environment);
                return JsonSerializer.Deserialize<SuiTransactionResult>(result) ?? throw new Exception();
            }
            catch (Exception ex)
            {
                throw new SuiApiException($"MintRegularCurrency: {ex.Message}");
            }
        }
    }

    public async Task<SuiTransactionResult> BurnRegularCurrency(List<RegularCoinBurnMessage> mintMessages)
    {
        using (new Measure($"Sui.BurnRegularCurrency"))
        {
            try
            {
                var environment = await _configuration.SuiEnvironment;
                var realmAccount = await _accountsService.GetOrCreateRealmAccount();
                var mintRequestJson = JsonSerializer.Serialize(mintMessages);
                var result = await NodeService.BurnRegularCoin(mintRequestJson, realmAccount.PrivateKey, environment);
                return JsonSerializer.Deserialize<SuiTransactionResult>(result) ?? throw new Exception();
            }
            catch (Exception ex)
            {
                throw new SuiApiException($"BurnRegularCurrency: {ex.Message}");
            }
        }
    }

    public async Task<SuiTransactionResult> MintGameCurrency(List<GameCoinMintMessage> mintMessages)
    {
        using (new Measure($"Sui.MintGameCurrency"))
        {
            try
            {
                var environment = await _configuration.SuiEnvironment;
                var realmAccount = await _accountsService.GetOrCreateRealmAccount();
                var mintRequestJson = JsonSerializer.Serialize(mintMessages);
                var result = await NodeService.MintGameCoin(mintRequestJson, realmAccount.PrivateKey, environment);
                return JsonSerializer.Deserialize<SuiTransactionResult>(result) ?? throw new Exception();
            }
            catch (Exception ex)
            {
                throw new SuiApiException($"MintGameCurrency: {ex.Message}");
            }
        }
    }

    public async Task<SuiTransactionResult> BurnGameCurrency(List<GameCoinBurnMessage> mintMessages)
    {
        using (new Measure($"Sui.BurnGameCurrency"))
        {
            try
            {
                var environment = await _configuration.SuiEnvironment;
                var realmAccount = await _accountsService.GetOrCreateRealmAccount();
                var mintRequestJson = JsonSerializer.Serialize(mintMessages);
                var result = await NodeService.BurnGameCoin(mintRequestJson, realmAccount.PrivateKey, environment);
                return JsonSerializer.Deserialize<SuiTransactionResult>(result) ?? throw new Exception();
            }
            catch (Exception ex)
            {
                throw new SuiApiException($"BurnGameCurrency: {ex.Message}");
            }
        }
    }

    public async Task<CoinBalanceResponse> GetCoinBalance(string wallet, CoinBalanceRequest request)
    {
        using (new Measure($"Sui.GetCoinBalance"))
        {
            try
            {
                var environment = await _configuration.SuiEnvironment;
                var requestJson = JsonSerializer.Serialize(request);
                var result = await NodeService.CoinBalance(wallet, requestJson, environment);
                return JsonSerializer.Deserialize<CoinBalanceResponse>(result) ?? throw new Exception();
            }
            catch (Exception ex)
            {
                throw new SuiApiException($"GetCoinBalance: {ex.Message}");
            }
        }
    }

    public async Task<GameCoinBalanceResponse> GetGameCoinBalance(string wallet, GameCoinBalanceRequest request)
    {
        using (new Measure($"Sui.GetGameCoinBalance"))
        {
            try
            {
                var environment = await _configuration.SuiEnvironment;
                var requestJson = JsonSerializer.Serialize(request);
                var result = await NodeService.GetGameCoinBalance(wallet, requestJson, environment);
                return JsonSerializer.Deserialize<GameCoinBalanceResponse>(result) ?? throw new Exception();
            }
            catch (Exception ex)
            {
                throw new SuiApiException($"GetGameCoinBalance: {ex.Message}");
            }
        }
    }

    public async Task<SuiTransactionResult> MintNfts(List<NftMintMessage> mintMessages)
    {
        using (new Measure($"Sui.MintNfts"))
        {
            try
            {
                var environment = await _configuration.SuiEnvironment;
                var realmAccount = await _accountsService.GetOrCreateRealmAccount();
                var mintRequestJson = JsonSerializer.Serialize(mintMessages);
                var result = await NodeService.MintNfts(mintRequestJson, realmAccount.PrivateKey, environment);
                return JsonSerializer.Deserialize<SuiTransactionResult>(result) ?? throw new Exception();
            }
            catch (Exception ex)
            {
                throw new SuiApiException($"MintNfts: {ex.Message}");
            }
        }
    }

    public async Task<IEnumerable<GetOwnedObjectsResponse>> GetOwnedObjects(string wallet, GetOwnedObjectsRequest request)
    {
        using (new Measure($"Sui.GetOwnedObjects"))
        {
            try
            {
                var environment = await _configuration.SuiEnvironment;
                var result = await NodeService.GetOwnedObjects(wallet, request.PackageId, environment);
                return JsonSerializer.Deserialize<IEnumerable<GetOwnedObjectsResponse>>(result) ?? throw new Exception();
            }
            catch (Exception ex)
            {
                throw new SuiApiException($"GetOwnedObjects: {ex.Message}");
            }
        }
    }

    public async Task<SuiTransactionResult> DeleteNft(List<NftDeleteMessage> request)
    {
        using (new Measure($"Sui.DeleteNft"))
        {
            try
            {
                var environment = await _configuration.SuiEnvironment;
                var realmAccount = await _accountsService.GetOrCreateRealmAccount();
                var mintRequestJson = JsonSerializer.Serialize(request);
                var result = await NodeService.DeleteNfts(mintRequestJson, realmAccount.PrivateKey, environment);
                return JsonSerializer.Deserialize<SuiTransactionResult>(result) ?? throw new Exception();
            }
            catch (Exception ex)
            {
                throw new SuiApiException($"DeleteNft: {ex.Message}");
            }
        }
    }

    public async Task<SuiTransactionResult> UpdateNft(List<NftUpdateMessage> request)
    {
        using (new Measure($"Sui.UpdateNft"))
        {
            try
            {
                var environment = await _configuration.SuiEnvironment;
                var realmAccount = await _accountsService.GetOrCreateRealmAccount();
                var mintRequestJson = JsonSerializer.Serialize(request);
                var result = await NodeService.UpdateNfts(mintRequestJson, realmAccount.PrivateKey, environment);
                return JsonSerializer.Deserialize<SuiTransactionResult>(result) ?? throw new Exception();
            }
            catch (Exception ex)
            {
                throw new SuiApiException($"UpdateNft: {ex.Message}");
            }
        }
    }

    public async Task<SuiTransactionResult> SetNftContractOwner(SetOwnerMessage message)
    {
        using (new Measure($"Sui.SetNftContractOwner"))
        {
            try
            {
                var environment = await _configuration.SuiEnvironment;
                var realmAccount = await _accountsService.GetOrCreateRealmAccount();
                var mintRequestJson = JsonSerializer.Serialize(message);
                var result = await NodeService.SetNftContractOwner(mintRequestJson, realmAccount.PrivateKey, environment);
                return JsonSerializer.Deserialize<SuiTransactionResult>(result) ?? throw new Exception();
            }
            catch (Exception ex)
            {
                throw new SuiApiException($"SetNftContractOwner: {ex.Message}");
            }
        }
    }

    public async Task<bool> ObjectExists(string objectId)
    {
        using (new Measure($"Sui.ObjectExists"))
        {
            try
            {
                var environment = await _configuration.SuiEnvironment;
                var result = await NodeService.ObjectExists(objectId, environment);
                if (bool.TryParse(result, out var exists))
                    return exists;
                return false;
            }
            catch (Exception ex)
            {
                throw new SuiApiException($"ObjectExists: {ex.Message}");
            }
        }
    }

    public async Task<SuiTransactionResult> WithdrawCurrency(GameCoinTransferMessage transferMessage)
    {
        using (new Measure($"Sui.WithdrawCurrency"))
        {
            try
            {
                var environment = await _configuration.SuiEnvironment;
                var realmAccount = await _accountsService.GetOrCreateRealmAccount();
                var requestJson = JsonSerializer.Serialize(transferMessage);
                var result = await NodeService.WithdrawCurrency(requestJson, realmAccount.PrivateKey, environment);
                return JsonSerializer.Deserialize<SuiTransactionResult>(result) ?? throw new Exception();
            }
            catch (Exception ex)
            {
                throw new SuiApiException($"WithdrawCurrency: {ex.Message}");
            }
        }
    }
}