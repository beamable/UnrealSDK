using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Beamable.SuiFederation.Features.Content.FunctionMessages;

public record RegularCoinMintMessage(
    string ContentId,
    string PackageId,
    string Module,
    string Function,
    string PlayerWalletAddress,
    string AdminCap,
    string TreasuryCap,
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
            Amount
        };

        return JsonSerializer.Serialize(selectedData);
    }
}

public static class RegularCoinMintMessageExtensions
{
    public static string SerializeSelected(this List<RegularCoinMintMessage> messages)
        => string.Join(",",messages.Select(m => m.SerializeSelected()));

    public static Dictionary<string, string> ToMetadata(this RegularCoinMintMessage message)
    {
        return new Dictionary<string, string>
        {
            { nameof(message.Amount), message.Amount.ToString() }
        };
    }
}