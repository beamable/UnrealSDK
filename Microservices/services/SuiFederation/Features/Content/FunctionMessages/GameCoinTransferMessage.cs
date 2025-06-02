using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Beamable.SuiFederation.Features.Content.FunctionMessages;

public record GameCoinTransferMessage(
    string ContentId,
    string PackageId,
    string Module,
    string Function,
    string PlayerWalletAddress,
    string PlayerWalletKey,
    long GamerTag,
    string TargetWalletAddress,
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
            TargetWalletAddress
        };

        return JsonSerializer.Serialize(selectedData);
    }
}

public static class GameCoinTransferMessageExtensions
{
    public static string SerializeSelected(this List<GameCoinTransferMessage> messages)
        => string.Join(",",messages.Select(m => m.SerializeSelected()));

    public static Dictionary<string, string> ToMetadata(this GameCoinTransferMessage message)
    {
        return new Dictionary<string, string>
        {
            { nameof(message.Amount), message.Amount.ToString() }
        };
    }
}