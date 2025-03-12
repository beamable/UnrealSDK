using System.Collections.Generic;
using System.Linq;
using System.Text.Json;
using Beamable.SuiFederation.Features.Content.Models;

namespace Beamable.SuiFederation.Features.Content.FunctionMessages;

public record NftMintMessage(
    string ContentId,
    string PackageId,
    string Module,
    string Function,
    string PlayerWalletAddress,
    string AdminCap,
    NftContentItem NftContentItem)
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
            NftContentItem.ContentId,
            NftContentItem.Name,
            NftContentItem.Description,
            NftContentItem.Url,
            NftContentItem.Attributes,
        };
        return JsonSerializer.Serialize(selectedData);
    }
}

public static class NftMintMessageExtensions
{
    public static string SerializeSelected(this List<NftMintMessage> messages)
        => string.Join(",",messages.Select(m => m.SerializeSelected()));

    public static Dictionary<string, string> ToMetadata(this NftMintMessage message)
        => message.NftContentItem.GetAttributes();
}