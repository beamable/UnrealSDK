using System;
using System.Threading.Tasks;
using Beamable.Common;

namespace Beamable.SuiFederation.Extensions;

public static class TaskExtensions
{
    public static async Task RunAsyncBlock(this Func<Task> task)
    {
        try
        {
            await task();
        }
        catch (Exception ex)
        {
            var error = $"Error running asyncBlock in method {task.Method.Name}. Error: {ex.ToLogFormat()}";
            BeamableLogger.LogError(error);
            throw;
        }
    }
}