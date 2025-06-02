using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

namespace Beamable.SuiFederation.Features.Content.FunctionMessages;

public record NftDeleteMessage(
    string ContentId,
    string PackageId,
    string Module,
    string Function,
    string PlayerWalletAddress,
    string ProxyId,
    string OwnerObjectId,
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
            ContentId
        };
        return JsonSerializer.Serialize(selectedData);
    }
}

public static class NftDeleteMessageExtensions
{
    public static string SerializeSelected(this List<NftDeleteMessage> messages)
        => string.Join(",",messages.Select(m => m.SerializeSelected()));
}