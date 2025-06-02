using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Beamable.SuiFederation.Extensions;

public static class ParallelExtensions
{
    public static async Task<Dictionary<TKey, List<TValue>>> ParallelGroupByAsync<TSource, TKey, TValue>(
        this IEnumerable<TSource> source,
        Func<TSource, Task<(TKey key, TValue? value)>> asyncSelector)
        where TKey : notnull
        where TValue : class
    {
        var resultDictionary = new ConcurrentDictionary<TKey, List<TValue>>();
        await Parallel.ForEachAsync(source, async (item, cancellationToken) =>
        {
            var (key, value) = await asyncSelector(item);
            if (value != null)
            {
                resultDictionary.AddOrUpdate(
                    key,
                    _ => [value],
                    (_, list) =>
                    {
                        lock (list)
                        {
                            list.Add(value);
                        }
                        return list;
                    }
                );
            }
        });

        return resultDictionary.ToDictionary(entry => entry.Key, entry => entry.Value);
    }

    public static async Task<Dictionary<TKey, List<TValue>>> GroupByAsync<TSource, TKey, TValue>(
        this IEnumerable<TSource> source,
        Func<TSource, Task<TValue?>> asyncSelector,
        Func<TValue, TKey> keySelector)
        where TKey : notnull
        where TValue : class
    {
        var resultDictionary = new Dictionary<TKey, List<TValue>>();

        foreach (var item in source)
        {
            var value = await asyncSelector(item);
            if (value == null) continue; // Ensure we don't store null values
            var key = keySelector(value);
            if (!resultDictionary.TryGetValue(key, out var list))
            {
                list = [];
                resultDictionary[key] = list;
            }
            list.Add(value);
        }
        return resultDictionary;
    }
}