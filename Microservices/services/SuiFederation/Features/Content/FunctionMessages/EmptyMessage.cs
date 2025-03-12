namespace Beamable.SuiFederation.Features.Content.FunctionMessages;

public record EmptyMessage(
    string ContentId,
    string PackageId,
    string Module,
    string Function,
    string PlayerWalletAddress)
    : BaseMessage(ContentId, PackageId, Module, Function, PlayerWalletAddress);

public static class EmptyMessageExtensions
{
    public static EmptyMessage Create() => new("", "", "", "", "");
}