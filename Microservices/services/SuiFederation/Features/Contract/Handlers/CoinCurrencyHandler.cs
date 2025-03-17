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

public class CoinCurrencyHandler : IService, IContentContractHandler
{
    private readonly ContractService _contractService;
    private readonly SuiClient _suiClient;
    private readonly SuiApiService _suiApiService;

    public CoinCurrencyHandler(ContractService contractService, SuiClient suiClient, SuiApiService suiApiService)
    {
        _contractService = contractService;
        _suiClient = suiClient;
        _suiApiService = suiApiService;
    }

    public async Task HandleContract(IContentObject clientContentInfo)
    {
        try
        {
            var contract = await _contractService.GetByContent<CoinContract>(clientContentInfo.Id);
            if (contract != null)
            {
                var objectExists = await _suiApiService.ObjectExists(contract.PackageId);
                if (objectExists)
                    return;
            }

            if (clientContentInfo is not CoinCurrency coinCurrency)
                throw new ContractException($"{clientContentInfo.Id} is not a {nameof(CoinCurrency)}");

            var itemTemplate = await File.ReadAllTextAsync("Features/Contract/Templates/coin.move");
            var template = Handlebars.Compile(itemTemplate);
            var itemResult = template(coinCurrency);
            var contractPath = $"{SuiFederationConfig.ContractSourcePath}{coinCurrency.ToModuleName()}.move";
            await ContractWriter.WriteContract(contractPath, itemResult);

            var deployOutput = await _suiClient.CompileAndPublish(coinCurrency.ToModuleName());

            await _contractService.UpsertContract(new CoinContract
            {
                PackageId = deployOutput.GetPackageId(),
                Module = coinCurrency.ToModuleName(),
                ContentId = coinCurrency.Id,
                TreasuryCap = GetCurrencyTreasuryCap(deployOutput),
                AdminCap = GetAdminCap(deployOutput, coinCurrency.ToModuleName())
            }, coinCurrency.Id);

            BeamableLogger.Log($"Created contract for {coinCurrency.Id}");
        }
        catch (Exception e)
        {
            throw new ContractException($"Error in creating contract for {clientContentInfo.Id}, exception: {e.Message}");
        }
    }

    private string GetCurrencyTreasuryCap(MoveDeployOutput deployOutput)
        => deployOutput.CreatedObjects.FirstOrDefault(obj => obj.ObjectType.StartsWith($"0x2::coin::TreasuryCap<{deployOutput.GetPackageId()}"))?.ObjectId
           ?? throw new ContractException("TreasuryCap not found.");

    private string GetAdminCap(MoveDeployOutput deployOutput, string moduleName)
        => deployOutput.CreatedObjects.FirstOrDefault(obj => obj.ObjectType.StartsWith($"{deployOutput.GetPackageId()}::{moduleName}::AdminCap"))?.ObjectId
           ?? throw new ContractException("AdminCap not found.");
}