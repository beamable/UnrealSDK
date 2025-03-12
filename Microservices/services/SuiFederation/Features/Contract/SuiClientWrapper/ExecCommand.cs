using System.Diagnostics;

namespace Beamable.SuiFederation.Features.Contract.SuiClientWrapper;

public static class ExecCommand
{
    private const int ProcessTimeoutMs = 60000;

    private static void ExecuteShell(string command, string? workingDirectory)
    {
        Execute("/bin/sh", $"-c \"{command}\"", workingDirectory);
    }

    private static void Execute(string program, string args, string? workingDirectory)
    {
        using var process = new Process();
        process.StartInfo =
            new ProcessStartInfo(program, args)
            {
                RedirectStandardOutput = true,
                RedirectStandardError = true,
                CreateNoWindow = true,
                UseShellExecute = false
            };

        if (!string.IsNullOrWhiteSpace(workingDirectory))
            process.StartInfo.WorkingDirectory = workingDirectory;

        process.Start();
        process.WaitForExit(ProcessTimeoutMs);
    }

}