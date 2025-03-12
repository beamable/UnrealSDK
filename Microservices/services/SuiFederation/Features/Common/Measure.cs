using System;
using System.Diagnostics;
using Beamable.Common;

namespace Beamable.SuiFederation.Features.Common;

internal readonly struct Measure : IDisposable
{
    private readonly string _operationName;
    private readonly long _startTime;

    public Measure(string operationName, bool disableMeasureLog = false)
    {
        _operationName = operationName;
        if (!disableMeasureLog)
        {
            BeamableLogger.Log("Starting {operation}", operationName);
            _startTime = Stopwatch.GetTimestamp();
        }
        else
        {
            _startTime = 0;
        }
    }

    public void Dispose()
    {
        if (_startTime > 0)
        {
            var elapsedSeconds = (Stopwatch.GetTimestamp() - _startTime) / (double)Stopwatch.Frequency;
            BeamableLogger.Log($"Done executing {_operationName} in {elapsedSeconds:F5} sec");
        }
    }
}