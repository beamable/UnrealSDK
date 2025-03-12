namespace Beamable.SuiFederation.Features.Content.FunctionMessages;

public abstract record BaseMessage(
    string ContentId,
    string PackageId,
    string Module,
    string Function,
    string PlayerWalletAddress);