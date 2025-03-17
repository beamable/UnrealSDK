using System;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Common.Content;
using Beamable.Common.Inventory;
using Beamable.SuiFederation.Features.Accounts;
using Beamable.SuiFederation.Features.Common;
using Beamable.SuiFederation.Features.Contract.Exceptions;
using Beamable.SuiFederation.Features.Contract.FunctionMesseges;
using Beamable.SuiFederation.Features.Contract.Handlers.Models;
using Beamable.SuiFederation.Features.Contract.Storage.Models;
using Beamable.SuiFederation.Features.Contract.SuiClientWrapper;
using Beamable.SuiFederation.Features.Contract.SuiClientWrapper.Models;
using Beamable.SuiFederation.Features.SuiApi;
using HandlebarsDotNet;
using SuiFederationCommon.Extensions;

namespace Beamable.SuiFederation.Features.Contract.Handlers;

public class NftContractHandler : IService, IContentContractHandler
{
    private readonly ContractService _contractService;
    private readonly SuiClient _suiClient;
    private readonly SuiApiService _suiApiService;
    private readonly AccountsService _accountsService;

    public NftContractHandler(ContractService contractService, SuiClient suiClient, SuiApiService suiApiService, AccountsService accountsService)
    {
        _contractService = contractService;
        _suiClient = suiClient;
        _suiApiService = suiApiService;
        _accountsService = accountsService;
    }

    public async Task HandleContract(IContentObject clientContentInfo)
    {
        try
        {
            var itemContent = clientContentInfo as ItemContent;
            var moduleName = FederationContentExtensions.SanitizeModuleName(itemContent!.ToModuleName());
            var contract = await _contractService.GetByContent<NftContract>(itemContent!.ContentType);
            if (contract != null)
            {
                var objectExists = await _suiApiService.ObjectExists(contract.PackageId);
                if (objectExists)
                    return;
            }

            var itemTemplate = await File.ReadAllTextAsync("Features/Contract/Templates/nft.move");
            var template = Handlebars.Compile(itemTemplate);
            var itemResult = template(new NftTemplate(moduleName));
            var contractPath = $"{SuiFederationConfig.ContractSourcePath}{moduleName}.move";
            await ContractWriter.WriteContract(contractPath, itemResult);

            var deployOutput = await _suiClient.CompileAndPublish(moduleName);

            var ownerObjectId = await CreateContractOwnerObject(deployOutput.GetPackageId(), moduleName, GetAdminCap(deployOutput, moduleName));

            await _contractService.UpsertContract(new NftContract
            {
                PackageId = deployOutput.GetPackageId(),
                Module = moduleName,
                ContentId = itemContent!.ContentType,
                AdminCap = GetAdminCap(deployOutput, moduleName),
                OwnerInfo = ownerObjectId
            }, itemContent!.ContentType);

            BeamableLogger.Log($"Created contract for {moduleName}");
        }
        catch (Exception e)
        {
            throw new ContractException($"Error in creating contract for {clientContentInfo.GetType()}, exception: {e.Message}");
        }
    }

    private async Task<string> CreateContractOwnerObject(string packageId, string moduleName, string adminCap)
    {
        try
        {
            var realmAccount = await _accountsService.GetOrCreateRealmAccount();
            var result = await _suiApiService.SetNftContractOwner(new SetOwnerMessage(packageId, moduleName, "set_owner", realmAccount.Address, adminCap));
            return result.objectIds[0];
        }
        catch (Exception e)
        {
            throw new ContractException($"Error in creating owner info for {moduleName}, exception: {e.Message}");
        }
    }

    private string GetAdminCap(MoveDeployOutput deployOutput, string moduleName)
        => deployOutput.CreatedObjects.FirstOrDefault(obj => obj.ObjectType.StartsWith($"{deployOutput.GetPackageId()}::{moduleName}::AdminCap"))?.ObjectId
           ?? throw new ContractException("AdminCap not found.");
}