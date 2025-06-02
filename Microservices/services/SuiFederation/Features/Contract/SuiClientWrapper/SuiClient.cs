using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text.Json;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.SuiFederation.Extensions;
using Beamable.SuiFederation.Features.Accounts;
using Beamable.SuiFederation.Features.Common;
using Beamable.SuiFederation.Features.Contract.SuiClientWrapper.Exceptions;
using Beamable.SuiFederation.Features.Contract.SuiClientWrapper.Models;

namespace Beamable.SuiFederation.Features.Contract.SuiClientWrapper;

public class SuiClient : IService
{
    private readonly Configuration _configuration;
    private readonly AccountsService _accountsService;

    private bool _initialized;
    private const string WorkingDirectory = "/beamApp";
    private const string SuiExecutable = "sui";
    private const int FaucetWaitTimeSec = 20;
    private const int ProcessTimeoutMs = 60000;

    public SuiClient(Configuration configuration, AccountsService accountsService)
    {
        _configuration = configuration;
        _accountsService = accountsService;
    }

    public async Task Initialize()
    {
        if (!_initialized)
        {
            try
            {
                var realmAccount = await _accountsService.GetOrCreateRealmAccount();
                await ExecuteShell("mkdir -p /root/.sui");
                await ExecuteShell($"cp -r {SuiFederationConfig.SuiClientConfigPath} /root/.sui");
                var suiEnvironment = await _configuration.SuiEnvironment;
                BeamableLogger.Log("Importing account.");
                await Execute(SuiExecutable, $"client switch --env {suiEnvironment}");
                var convertedKey = await Execute(SuiExecutable, $"keytool convert --json {realmAccount.PrivateKey}");
                var keyToolConvert = JsonSerializer.Deserialize<KeyToolConvert>(convertedKey);
                await Execute(SuiExecutable, $"keytool import {keyToolConvert!.Bench32Format} ed25519");
                await Execute(SuiExecutable, $"client switch --address {realmAccount.Address}");
                _initialized = true;

                if (suiEnvironment is "devnet")
                {
                    var balanceJson = await Execute(SuiExecutable, $"client gas --json", ignoreOutputError: true);
                    var gasBalances = JsonSerializer.Deserialize<List<GasBalanceItem>>(balanceJson) ?? [];
                    var balance = gasBalances.Sum(b => b.GasBalance);
                    BeamableLogger.Log($"Gas balance is {balance}.");
                    if (balance.ToSui() < 5)
                    {
                        BeamableLogger.Log($"Requesting faucet coins, waiting {FaucetWaitTimeSec} sec...");
                        await Execute(SuiExecutable, $"client faucet");
                        await Task.Delay(TimeSpan.FromSeconds(FaucetWaitTimeSec));
                        BeamableLogger.Log("Done requesting faucet coins.");
                    }
                }
            }
            catch (Exception e)
            {
                throw new SuiClientException($"Failed to initialize SUI client: {e.Message}");
            }
        }
    }

    public async Task<MoveDeployOutput> CompileAndPublish(string moduleName)
    {
        try
        {
            BeamableLogger.Log($"Compiling smart contract for {moduleName}...");
            await Execute(SuiExecutable, $"move new -p move/{moduleName}_package {moduleName}_package", ignoreOutput: true);
            await ExecuteShell($"rm -r move/{moduleName}_package/tests");
            await ExecuteShell($"rm move/{moduleName}_package/sources/{moduleName}_package.move");
            await ExecuteShell($"cp move/sources/{moduleName}.move move/{moduleName}_package/sources");
            await ExecuteShell($"sed -i 's/rev = \"framework\\/[^\"]*\"/rev = \"framework\\/{await _configuration.SuiEnvironment}\"/' move/{moduleName}_package/Move.toml");
            await Execute(SuiExecutable, $"move build -p move/{moduleName}_package --silence-warnings", ignoreOutput: true);
            BeamableLogger.Log($"Deploying smart contract for {moduleName}...");
            var deployOutputData = await Execute(SuiExecutable,
                $"client publish --silence-warnings --skip-dependency-verification --json move/{moduleName}_package",
                ignoreOutputError: true);
            var deployOutput = JsonSerializer.Deserialize<MoveDeployOutput>(deployOutputData) ?? new MoveDeployOutput();
            BeamableLogger.Log($"Deployed package {deployOutput.GetPackageId()}");
            return deployOutput;
        }
        catch (Exception ex)
        {
            BeamableLogger.LogError("SmartContract compile error: {processOutput}", ex.Message);
            throw new SuiClientException(ex.Message);
        }
    }

    private static async Task<string> ExecuteShell(string command, string workingDirectory = WorkingDirectory)
    {
        //return await Execute("/bin/sh", $"-c \"{command}\"", workingDirectory);
        return await Execute("/bin/sh", $"-c \"{command.Replace("\"", "\\\"")}\"", workingDirectory);
    }

    private static async Task<string> Execute(string program, string args, string workingDirectory = WorkingDirectory, bool ignoreOutput = false, bool ignoreOutputError = true)
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

        if (!ignoreOutput)
        {

            var outputText = await process.StandardOutput.ReadToEndAsync();
            var outputError = await process.StandardError.ReadToEndAsync();

            process.WaitForExit(ProcessTimeoutMs);

            if (!string.IsNullOrEmpty(outputError) && !ignoreOutputError)
            {
                BeamableLogger.LogError("Process error: {processOutput}", outputError);
                throw new SuiClientException(outputError);
            }

            BeamableLogger.Log("Process output: {processOutput}", outputText);
            return outputText;
        }
        process.WaitForExit(ProcessTimeoutMs);
        return string.Empty;
    }

}