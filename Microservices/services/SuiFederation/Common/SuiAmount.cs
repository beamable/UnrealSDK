using System;
using System.Globalization;

namespace Beamable.SuiFederation.Common;

public readonly record struct SuiAmount
{
    private const int NativeDecimals = 9;
    private long TotalUnits { get; }
    private int Decimals { get; }

    public static readonly SuiAmount NativeZero = new(0);

    public SuiAmount(long totalUnits, int decimals = NativeDecimals)
    {
        if (decimals is < 0 or > 9)
            throw new ArgumentOutOfRangeException(nameof(decimals), "Decimals must be between 0 and 9.");

        TotalUnits = totalUnits;
        Decimals = decimals;
    }

    public static SuiAmount Parse(string amount, int decimals = NativeDecimals)
    {
        if (amount is null)
            throw new ArgumentNullException(nameof(amount));

        if (!decimal.TryParse(amount, NumberStyles.Any, CultureInfo.InvariantCulture, out var decimalAmount))
            throw new FormatException($"Invalid amount format: '{amount}'");

        return FromDecimal(decimalAmount, decimals);
    }

    public static SuiAmount FromDecimal(decimal amount, int decimals = NativeDecimals)
    {
        if (decimals is < 0 or > 9)
            throw new ArgumentOutOfRangeException(nameof(decimals), "Decimals must be between 0 and 9.");

        var factor = (decimal)Math.Pow(10, decimals);
        var totalUnits = (long)Math.Round(amount * factor);
        return new SuiAmount(totalUnits, decimals);
    }

    public static SuiAmount FromLong(long amount, int decimals = NativeDecimals)
    {
        if (decimals is < 0 or > 9)
            throw new ArgumentOutOfRangeException(nameof(decimals), "Decimals must be between 0 and 9.");

        var factor = (decimal)Math.Pow(10, decimals);
        var totalUnits = (long)Math.Round(amount * factor);
        return new SuiAmount(totalUnits, decimals);
    }

    public decimal ToSui()
    {
        if (Decimals == 0) return TotalUnits;
        var factor = (decimal)Math.Pow(10, Decimals);
        return TotalUnits / factor;
    }

    public string ToSuiString()
    {
        var value = ToSui();
        var format = "F" + Decimals.ToString(CultureInfo.InvariantCulture);
        return value.ToString(format, CultureInfo.InvariantCulture);
    }

    public override string ToString()
    {
        return ToSuiString();
    }

    private static void EnsureMatchingDecimals(SuiAmount a, SuiAmount b)
    {
        if (a.Decimals != b.Decimals)
        {
            throw new InvalidOperationException(
                $"Cannot perform arithmetic on amounts with different decimal precisions ({a.Decimals} and {b.Decimals}).");
        }
    }

    public static implicit operator long(SuiAmount amount) => amount.TotalUnits;

    public static implicit operator SuiAmount(long mist) =>
        new (mist, NativeDecimals);

    public static SuiAmount operator +(SuiAmount a, SuiAmount b)
    {
        EnsureMatchingDecimals(a, b);
        return new SuiAmount(checked(a.TotalUnits + b.TotalUnits), a.Decimals);
    }

    public static SuiAmount operator +(SuiAmount a, long b)
    {
        return new SuiAmount(checked(a.TotalUnits + b), a.Decimals);
    }

    public static SuiAmount operator -(SuiAmount a, SuiAmount b)
    {
        EnsureMatchingDecimals(a, b);
        return new SuiAmount(checked(a.TotalUnits - b.TotalUnits), a.Decimals);
    }
}