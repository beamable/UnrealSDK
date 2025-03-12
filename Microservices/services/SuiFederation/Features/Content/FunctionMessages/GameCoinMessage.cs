using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Beamable.SuiFederation.Features.Content.FunctionMessages;

public record GameCoinMintMessage(
    string ContentId,
    string PackageId,
    string Module,
    string Function,
    string PlayerWalletAddress,
    string AdminCap,
    string TokenPolicyCap,
    string TokenPolicy,
    string Store,
    long Amount)
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
            Amount,
            Store
        };

        return JsonSerializer.Serialize(selectedData);
    }
}

public static class GameCoinMintMessageExtensions
{
    public static string SerializeSelected(this List<GameCoinMintMessage> messages)
        => string.Join(",",messages.Select(m => m.SerializeSelected()));

    public static Dictionary<string, string> ToMetadata(this GameCoinMintMessage message)
    {
        return new Dictionary<string, string>
        {
            { nameof(message.Amount), message.Amount.ToString() }
        };
    }
}