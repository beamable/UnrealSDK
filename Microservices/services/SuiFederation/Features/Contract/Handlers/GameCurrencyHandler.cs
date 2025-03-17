using System;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Common.Content;
using Beamable.SuiFederation.Features.Common;
using Beamable.SuiFederation.Features.Contract.Exceptions;
using Beamable.SuiFederation.Features.Contract.Storage.Models;
using Beamable.SuiFederation.Features.Contract.SuiClientWrapper;
using Beamable.SuiFederation.Features.Contract.SuiClientWrapper.Models;
using Beamable.SuiFederation.Features.SuiApi;
using HandlebarsDotNet;
using SuiFederationCommon.Extensions;
using SuiFederationCommon.FederationContent;

namespace Beamable.SuiFederation.Features.Contract.Handlers;

public class GameCurrencyHandler : IService, IContentContractHandler
{
    private readonly ContractService _contractService;
    private readonly SuiClient _suiClient;
    private readonly SuiApiService _suiApiService;

    public GameCurrencyHandler(ContractService contractService, SuiClient suiClient, SuiApiService suiApiService)
    {
        _contractService = contractService;
        _suiClient = suiClient;
        _suiApiService = suiApiService;
    }

    public async Task HandleContract(IContentObject clientContentInfo)
    {
        try
        {
            var contract = await _contractService.GetByContent<GameCoinContract>(clientContentInfo.Id);
            if (contract != null)
            {
                var objectExists = await _suiApiService.ObjectExists(contract.PackageId);
                if (objectExists)
                    return;
            }

            if (clientContentInfo is not InGameCurrency coinCurrency)
                throw new ContractException($"{clientContentInfo.Id} is not a {nameof(GameCoinContract)}");

            var itemTemplate = await File.ReadAllTextAsync("Features/Contract/Templates/game_coin.move");
            var template = Handlebars.Compile(itemTemplate);
            var itemResult = template(coinCurrency);
            var contractPath = $"{SuiFederationConfig.ContractSourcePath}{coinCurrency.ToModuleName()}.move";
            await ContractWriter.WriteContract(contractPath, itemResult);

            var deployOutput = await _suiClient.CompileAndPublish(coinCurrency.ToModuleName());

            await _contractService.UpsertContract(new GameCoinContract
            {
                PackageId = deployOutput.GetPackageId(),
                Module = coinCurrency.ToModuleName(),
                ContentId = coinCurrency.Id,
                AdminCap = GetAdminCap(deployOutput, coinCurrency.ToModuleName()),
                TokenPolicy = GetTokenPolicy(deployOutput),
                TokenPolicyCap = GetTokenPolicyCap(deployOutput),
                Store = GetStore(deployOutput, coinCurrency.ToModuleName())
            }, coinCurrency.Id);

            BeamableLogger.Log($"Created contract for {coinCurrency.Id}");
        }
        catch (Exception e)
        {
            throw new ContractException($"Error in creating contract for {clientContentInfo.Id}, exception: {e.Message}");
        }
    }

    private string GetStore(MoveDeployOutput deployOutput, string moduleName)
        => deployOutput.CreatedObjects.FirstOrDefault(obj =>
            obj.ObjectType.StartsWith(
                $"{deployOutput.GetPackageId()}::{moduleName}::{moduleName}Store",
                StringComparison.OrdinalIgnoreCase
            )
        )?.ObjectId ?? throw new ContractException("Token store not found.");
    private string GetTokenPolicy(MoveDeployOutput deployOutput)
        => deployOutput.CreatedObjects.FirstOrDefault(obj => obj.ObjectType.StartsWith($"0x2::token::TokenPolicy<{deployOutput.GetPackageId()}"))?.ObjectId
           ?? throw new ContractException("TokenPolicy not found.");

    private string GetTokenPolicyCap(MoveDeployOutput deployOutput)
        => deployOutput.CreatedObjects.FirstOrDefault(obj => obj.ObjectType.StartsWith($"0x2::token::TokenPolicyCap<{deployOutput.GetPackageId()}"))?.ObjectId
           ?? throw new ContractException("TokenPolicyCap not found.");

    private string GetAdminCap(MoveDeployOutput deployOutput, string moduleName)
        => deployOutput.CreatedObjects.FirstOrDefault(obj => obj.ObjectType.StartsWith($"{deployOutput.GetPackageId()}::{moduleName}::AdminCap"))?.ObjectId
           ?? throw new ContractException("AdminCap not found.");
}