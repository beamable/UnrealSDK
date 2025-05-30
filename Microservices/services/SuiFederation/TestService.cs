using System.Threading.Tasks;
using Beamable.SuiFederation.Features.Accounts;
using Beamable.SuiFederation.Features.Content.FunctionMessages;
using Beamable.SuiFederation.Features.Contract;
using Beamable.SuiFederation.Features.Contract.Storage.Models;
using Beamable.SuiFederation.Features.SuiApi;

namespace Beamable.SuiFederation;

public class TestService : IService
{
    private readonly SuiApiService _suiApiService;
    private readonly AccountsService _accountsService;
    private readonly ContractService _contractService;

    public TestService(SuiApiService suiApiService, AccountsService accountsService, ContractService contractService)
    {
        _suiApiService = suiApiService;
        _accountsService = accountsService;
        _contractService = contractService;
    }

    public async Task Test()
    {
        var contract = await _contractService.GetByContentId<GameCoinContract>("currency.game_coin.gold");
        var key = await _accountsService.GetAccountByAddress("0xf4bf966c4ca74ee925eebe0995ef85c0c42a1164ed05246bc6668224d6436e3a");
        await _suiApiService.BurnGameCurrency([
            new GameCoinBurnMessage(
                "currency.game_coin.gold",
                contract.PackageId,
                "gold",
                "burn",
                key!.Address,
                contract.AdminCap,
                contract.TokenPolicyCap,
                contract.TokenPolicy,
                contract.Store,
                1,
                key!.PrivateKey
            )
        ]);
    }
}