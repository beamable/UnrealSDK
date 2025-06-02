namespace Beamable.SuiFederation.Features.Withdrawal.Models;

public class WithdrawalRequest
{
    public required string ContentId { get; set; }
    public required long Amount { get; set; }
    public required long GamerTag { get; set; }
}