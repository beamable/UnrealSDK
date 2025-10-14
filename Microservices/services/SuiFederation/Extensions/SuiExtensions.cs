namespace Beamable.SuiFederation.Extensions;

public static class SuiExtensions
{
    public const long MistPerSui = 1_000_000_000;

    public static decimal ToSui(this long mist)
    {
        return (decimal)mist / MistPerSui;
    }

    public static long ToMist(this decimal sui)
    {
        return (long)(sui * MistPerSui);
    }
}