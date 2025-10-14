namespace Beamable.SuiFederation.Features.WalletManager.Models;

public readonly record struct SuiLockRequest(long Amount, string CoinPackage, string CoinModule)
{
    public static SuiLockRequest Default() => new(500_000_000, "0x0000000000000000000000000000000000000000000000000000000000000002", "sui");
}