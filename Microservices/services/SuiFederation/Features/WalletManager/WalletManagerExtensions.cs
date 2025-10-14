using System;
using System.Collections.Generic;
using System.Linq;
namespace Beamable.SuiFederation.Features.WalletManager;

public static class WalletManagerExtensions
{
    private static readonly Random Rng = new ();

    public static IEnumerable<int> GenerateRandomList(int length, List<int> excludedNumbers)
    {
        var numbers = Enumerable.Range(1, length).Where(n => !excludedNumbers.Contains(n)).ToArray();
        var n = numbers.Length;
        while (n > 1)
        {
            n--;
            var k = Rng.Next(n + 1);
            (numbers[k], numbers[n]) = (numbers[n], numbers[k]);
            yield return numbers[n];
        }
        if (n == 1)
        {
            yield return numbers[0];
        }
    }

    public static void ShuffleList<T>(List<T> list)
    {
        var n = list.Count;
        while (n > 1)
        {
            n--;
            var k = Rng.Next(n + 1);
            (list[k], list[n]) = (list[n], list[k]);
        }
    }

    public static long SafeDivide(long numerator, long denominator)
    {
        if (denominator == 0)
            return 0;
        try
        {
            return numerator / denominator;
        }
        catch (Exception)
        {
            return 0;
        }
    }
}