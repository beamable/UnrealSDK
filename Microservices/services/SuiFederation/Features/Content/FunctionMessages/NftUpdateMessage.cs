using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Beamable.SuiFederation.Features.Content.Models;

namespace Beamable.SuiFederation.Features.Content.FunctionMessages;

public record NftUpdateMessage(
    string ContentId,
    string PackageId,
    string Module,
    string Function,
    string PlayerWalletAddress,
    string ProxyId,
    string OwnerObjectId,
    string PlayerWalletKey,
    NftAttribute[] Attributes)
    : BaseMessage(ContentId, PackageId, Module, Function, PlayerWalletAddress)
{
    public string SerializeSelected()
    {
        var attributes = string.Join(", ", Attributes.Select(a => $"{a.Name}: {a.Value}"));
        var selectedData = new
        {
            PackageId,
            Module,
            Function,
            PlayerWalletAddress,
            ContentId,
            attributes
        };
        return JsonSerializer.Serialize(selectedData);
    }
}

public static class NftUpdateMessageExtensions
{
    public static string SerializeSelected(this List<NftUpdateMessage> messages)
        => string.Join(",",messages.Select(m => m.SerializeSelected()));
}