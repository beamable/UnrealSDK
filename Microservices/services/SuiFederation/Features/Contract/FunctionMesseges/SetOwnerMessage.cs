using System.Text.Json;
using Beamable.SuiFederation.Features.Content.FunctionMessages;

namespace Beamable.SuiFederation.Features.Contract.FunctionMesseges;

public record SetOwnerMessage(
    string PackageId,
    string Module,
    string Function,
    string PlayerWalletAddress,
    string AdminCap)
    : BaseMessage("", PackageId, Module, Function, PlayerWalletAddress)
{
    public string SerializeSelected()
    {
        var selectedData = new
        {
            PackageId,
            Module,
            Function,
            PlayerWalletAddress,
        };
        return JsonSerializer.Serialize(selectedData);
    }
}