using System;
using System.Threading;
using System.Threading.Channels;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Server;

namespace Beamable.SuiFederation.Features.ChannelProcessor;

public static class ChannelService
{
    private static readonly Channel<ChannelWorkItem> Channel = System.Threading.Channels.Channel.CreateUnbounded<ChannelWorkItem>();
    private static int _queueLength;
    private static bool _isStarted;

    public static async Task Enqueue(long gamerTag, Func<long, Task> input)
    {
        var tcs = new TaskCompletionSource();
        Interlocked.Increment(ref _queueLength);
        await Channel.Writer.WriteAsync(new ChannelWorkItem(
            async (userHandler) =>
            {
                try
                {
                    await input(userHandler);
                    tcs.SetResult();
                }
                catch (Exception ex)
                {
                    tcs.SetException(ex);
                    BeamableLogger.LogWarning("ChannelService Enqueue exception: {ex}", ex);
                }
                finally
                {
                    Interlocked.Decrement(ref _queueLength);
                }
            },
            gamerTag
        ));
    }

    public static void Start()
    {
        if (_isStarted)
            return;
        _ = Task.Run(async () =>
        {
            await foreach (var workItem in Channel.Reader.ReadAllAsync())
            {
                try
                {
                    await workItem.Work(workItem.GamerTag);
                }
                catch (Exception ex)
                {
                    BeamableLogger.LogWarning("ChannelService Start exception: {ex}", ex);
                }
            }
        });
        _isStarted = true;
    }

    public static int GetQueueLength() => _queueLength;
}

public record ChannelWorkItem(Func<long, Task> Work, long GamerTag);