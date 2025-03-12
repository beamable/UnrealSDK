using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Beamable.SuiFederation.Features.Content.FunctionMessages;

public record RegularCoinBurnMessage(
    string ContentId,
    string PackageId,
    string Module,
    string Function,
    string PlayerWalletAddress,
    string TreasuryCap,
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

public static class RegularCoinBurnMessageExtensions
{
    public static string SerializeSelected(this List<RegularCoinBurnMessage> messages)
        => string.Join(",",messages.Select(m => m.SerializeSelected()));

    public static Dictionary<string, string> ToMetadata(this RegularCoinBurnMessage message)
    {
        return new Dictionary<string, string>
        {
            { nameof(message.Amount), message.Amount.ToString() }
        };
    }
}