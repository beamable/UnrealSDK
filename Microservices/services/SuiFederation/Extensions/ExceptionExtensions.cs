using System;

namespace Beamable.SuiFederation.Extensions;

public static class ExceptionExtensions
{
    public static string ToLogFormat(this Exception exception)
    {
        return $"[Exception] {exception?.GetType()} {exception?.Message} {exception?.StackTrace}";
    }
}