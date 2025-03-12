namespace Beamable.SuiFederation.Features.SuiApi.Models;

public record SuiTransactionResult(
    string status,
    string digest,
    string gasUsed,
    string[] objectIds,
    string error);