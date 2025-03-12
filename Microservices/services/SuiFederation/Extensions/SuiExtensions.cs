namespace Beamable.SuiFederation.Extensions;

public static class SuiExtensions
{
    private const decimal MistToSui = 1000000000m; // 1 SUI = 1,000,000,000 MIST

    public static decimal ToSui(this long mist)
    {
        return mist / MistToSui;
    }

    public static long ToMist(this decimal sui)
    {
        return (long)(sui * MistToSui);
    }
}