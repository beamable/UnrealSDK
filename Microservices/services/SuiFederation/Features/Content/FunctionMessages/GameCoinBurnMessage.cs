using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Beamable.SuiFederation.Features.Content.FunctionMessages;

public record GameCoinBurnMessage(
    string ContentId,
    string PackageId,
    string Module,
    string Function,
    string PlayerWalletAddress,
    string AdminCap,
    string TokenPolicyCap,
    string TokenPolicy,
    string Store,
    long Amount,
    string PlayerWalletKey)
    : BaseMessage(ContentId, PackageId, Module, Function, PlayerWalletAddress)
{
    public string SerializeSelected()
    {
        var selectedData = new
        {
            PackageId,
            Module,
            Function,
            PlayerWalletAddress,
            Amount
        };

        return JsonSerializer.Serialize(selectedData);
    }
}

public static class GameCoinBurnMessageExtensions
{
    public static string SerializeSelected(this List<GameCoinBurnMessage> messages)
        => string.Join(",",messages.Select(m => m.SerializeSelected()));
}