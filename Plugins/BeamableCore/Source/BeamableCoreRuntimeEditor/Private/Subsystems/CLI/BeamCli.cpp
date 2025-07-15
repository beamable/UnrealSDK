// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/CLI/BeamCli.h"

#include "HttpModule.h"
#include "RequestTracker/BeamRequestTracker.h"
#include "Subsystems/BeamEditor.h"
#include "Subsystems/CLI/BeamCliCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliConfigCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliInitCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliServerServeCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliVersionCommand.h"


FBeamOperationHandle UBeamCli::InitializeWhenEditorReady()
{
	FPlatformMisc::SetEnvironmentVar(TEXT("DOTNET_CLI_UI_LANGUAGE"), TEXT("en"));
	const auto Op = RequestTracker->CPP_BeginOperation({}, GetName(), {});

	// Make sure we have the BeamCliVersion.txt file
	FString DotnetTools;
	if (const auto Path = FPaths::ProjectDir() / TEXT(".config/dotnet-tools.json"); !FFileHelper::LoadFileToString(DotnetTools, *Path))
	{
		const auto Err = FString::Printf(TEXT(
			"Found no .config/dotnet-tools.json. You have likely misconfigured Beamable. Please refer to our Getting Started documentation. It explains what this file is and how to set it up."));

		RequestTracker->TriggerOperationError(Op, Err);
		return Op;
	}

	FJsonDataBag Bag;
	if (!Bag.FromJson(DotnetTools))
	{
		const auto Err = FString::Printf(TEXT(
			"Found .config/dotnet-tools.json is not a valid JSON object. You have likely misconfigured Beamable. Please refer to our Getting Started documentation. It explains what this file is and how to set it up."));

		RequestTracker->TriggerOperationError(Op, Err);
		return Op;
	}

	const TSharedPtr<FJsonObject> ToolsArray = Bag.GetField(TEXT("tools"))->AsObject();
	const TSharedPtr<FJsonObject>* BeamableToolObj;
	if (!ToolsArray->TryGetObjectField(TEXT("beamable.tools"), BeamableToolObj))
	{
		const auto Err = FString::Printf(TEXT(
			"Found .config/dotnet-tools.json has no 'beamable.tools' entry. You have likely misconfigured Beamable. Please refer to our Getting Started documentation. It explains what this file is and how to set it up."));

		RequestTracker->TriggerOperationError(Op, Err);
		return Op;
	}

	FString ExpectedVersion;
	if (!(*BeamableToolObj)->TryGetStringField(TEXT("version"), ExpectedVersion))
	{
		const auto Err = FString::Printf(TEXT(
			"Found .config/dotnet-tools.json has no 'version' field in its 'beamable.tools' entry. You have likely misconfigured Beamable. Please refer to our Getting Started documentation. It explains what this file is and how to set it up."));

		RequestTracker->TriggerOperationError(Op, Err);
		return Op;
	}


	// Try to run the CLI once just to see if it is installed. If Launch returns "true", that means the CLI was found in this machine's PATH. 
	IsInstalledProcess = MakeUnique<FMonitoredProcess>(UBeamCliCommand::GetDotnetPath(), TEXT("beam version"), FPaths::ProjectDir(), true, true);
	IsInstalledProcess->OnOutput().BindLambda([this, Op, ExpectedVersion](const FString& InstalledVersion)
	{
		// We dispatch to the GameThread as triggering operation events should always be done in the GameThread.
		UE_LOG(LogBeamCli, Verbose, TEXT("Found Local BeamCLI with version: %s. Dispatching to GameThread so we can complete the operation."), *InstalledVersion)
		AsyncTask(ENamedThreads::GameThread, [this, Op, InstalledVersion, ExpectedVersion]
		{
			UE_LOG(LogBeamCli, Display, TEXT("Found Local BeamCLI with version: %s"), *InstalledVersion)

			// If we don't have the expected version (AND the version we expect is not 
			if (!InstalledVersion.Contains(ExpectedVersion) && !ExpectedVersion.Contains("0.0.123"))
			{
				bInstalled = FOptionalBool{false};
				FString Err = FString::Printf(TEXT("Beam CLI Version Mismatch (Installed = %s, Expected= %s). Please make sure your installed Beamable CLI version is correct."),
				                              *InstalledVersion, *ExpectedVersion);

				RequestTracker->TriggerOperationError(Op, Err);
			}
		});
	});
	IsInstalledProcess->OnCompleted().BindLambda([this, Op, ExpectedVersion](int ResCode)
	{
		AsyncTask(ENamedThreads::GameThread, [this, Op, ResCode, ExpectedVersion]
		{
			// Kick off our CLI running in server mode ONLY if the version command worked as expected.
			if (ResCode == 0)
			{
				bInstalled = FOptionalBool{true};
				RequestTracker->TriggerOperationSuccess(Op, "");
			}
			else
			{
				bInstalled = FOptionalBool{false};
				const auto Err = FString::Printf(TEXT("Failed to run `dotnet beam`. Take a look at the logs for more information. Try running a `dotnet tool restore` and re-running the editor."));
				RequestTracker->TriggerOperationError(Op, Err);
			}
		});
	});

	// If we couldn't find a local CLI version --- set it as false.
	if (!IsInstalledProcess->Launch())
	{
		IsInstalledProcess = MakeUnique<FMonitoredProcess>(UBeamCliCommand::GetDotnetPath(), TEXT("--version"), FPaths::ProjectDir(), true, false);
		const auto didLaunchDotnet = IsInstalledProcess->Launch();
		if (!didLaunchDotnet)
		{
			const auto Err = FString::Printf(TEXT("Failed to run `dotnet` that is required for CLI integration to work. Try setting up value for dotnet to use manually in BeamEditorSettings and try again."));
			RequestTracker->TriggerOperationError(Op, Err);
		}
		else
		{
			UE_LOG(LogBeamCli, Warning, TEXT("No local CLI version installed. The issue can be also due to not being able to find dotnet."));
			bInstalled = FOptionalBool{false};
		}
	}

	// If we couldn't find a local CLI version, we return a successful op instead, but... we set the target realm to be the one from `.beamable/connection-configuration.json`.
	if (bInstalled.IsSet && !bInstalled.Val)
	{
		const auto NoCliErr = FString::Printf(TEXT("Beam CLI not found. Please make sure you have an installed Beamable CLI (Version: %s) if you want to use any editor features."), *DotnetTools);
		RequestTracker->TriggerOperationSuccess(Op, NoCliErr);
	}

	return Op;
}

FBeamOperationHandle UBeamCli::InitializeRealm(FBeamRealmHandle NewRealm)
{
	FBeamRealmUser EditorUserData;
	const auto Slot = Editor->GetMainEditorSlot(EditorUserData);

	if (!IsInstalled())
	{
		UE_LOG(LogBeamCli, Error, TEXT("CLI not installed or not detected. Please make sure you have the CLI installed!"))
		return RequestTracker->CPP_BeginSuccessfulOperation({Slot}, GetName(), TEXT("CLI not installed or not detected. Please make sure you have the CLI installed!"), {});
	}

	return RequestTracker->CPP_BeginSuccessfulOperation({Slot}, GetName(), TEXT("CLI is installed."), {});
}

void UBeamCli::StartCliServer(bool bSkipPrewarm)
{
	// Ensure the CLI is installed
	if (!IsInstalled())
	{
		UE_LOG(LogBeamCli, Error, TEXT("CLI was not found locally. This system is not guaranteed to work because of this."));
		return;
	}

	// Run the server command so we boot the server up --- when its up, run the intended command.
	auto ServerStartHandler = FBeamOperationEventHandlerCode::CreateLambda([this](FBeamOperationEvent Evt)
	{
		if (Evt.EventType == OET_SUCCESS)
		{
			CurrentCliServerUri = Evt.EventCode;

			// Run and clear all enqueued processes
			for (FBeamEnqueuedCliCommand EnqueuedCommand : EnqueuedProcesses)
			{
				UE_LOG(LogBeamCli, Display, TEXT("Now executing command. CMD=%s"), *EnqueuedCommand.CliCommand->GetClass()->GetName());
				EnqueuedCommand.CliCommand->RunServer(Evt.EventCode, EnqueuedCommand.Params, EnqueuedCommand.Op);
				RunningProcesses.Add(EnqueuedCommand.CliCommand);
			}
			EnqueuedProcesses.Empty();
		}
		else
		{
			UE_LOG(LogBeamCli, Error, TEXT("Should not be seeing this. If you do see it, please report a bug to Beamable."));
		}
	});
	const auto ServerStartOp = RequestTracker->CPP_BeginOperation({}, GetName(), ServerStartHandler);

	const auto ServerCmd = NewObject<UBeamCliServerServeCommand>();
	ServerCmd->OnStreamOutput = [this, ServerStartOp](const TArray<UBeamCliServerServeStreamData*>& Stream, const TArray<int64>&, const FBeamOperationHandle&)
	{
		CurrentCliServerUri = Stream[0]->Uri;

		// Complete the given operation
		if (RequestTracker->ActiveOperations.Contains(ServerStartOp) && RequestTracker->ActiveOperationState[ServerStartOp]->Status == 0)
			RequestTracker->TriggerOperationSuccess(ServerStartOp, Stream[0]->Uri);

		UE_LOG(LogBeamCli, Display, TEXT("SERVER CLI STARTED. PORT=%d, URI=%s"), Stream[0]->Port, *Stream[0]->Uri)
	};

	ServerCmd->OnCompleted = [this](const int& ResCode, const FBeamOperationHandle&)
	{
		CurrentCliServerUri = TEXT("");
		UE_LOG(LogBeamCli, Display, TEXT("On SERVER CLI TERMINATED %d"), ResCode)
	};

	TArray<FString> Params;
	Params.Append({TEXT("--require-process-id"), FString::Printf(TEXT("%u"), FPlatformProcess::GetCurrentProcessId())});
	Params.Append({TEXT("-d"), TEXT("0")});
	Params.Append({TEXT("-cs")});
	if (bSkipPrewarm) Params.Append({TEXT("-scpw")});

	RunCommand(ServerCmd, Params, ServerStartOp);
}

void UBeamCli::StopCli()
{
	// Gather all running CLI commands. 
	TArray<UBeamCliCommand*> ToStop = {};
	for (UBeamCliCommand* RunningProcess : RunningProcesses)
		ToStop.Add(RunningProcess);

	// Stops all of them
	for (UBeamCliCommand* Stop : ToStop)
		StopCommand(Stop);

	// Clear the Server URI so that the next command invocation re-starts it.
	CurrentCliServerUri.Empty();
}

void UBeamCli::RunCommand(UBeamCliCommand* Command, const TArray<FString>& Params, const FBeamOperationHandle& Op)
{
	// Ensure the CLI is installed
	if (!IsInstalled())
	{
		UE_LOG(LogBeamCli, Error, TEXT("CLI was not found locally. This system is not guaranteed to work because of this."));
		return;
	}

	Command->Run(Params, Op);
	RunningProcesses.Add(Command);
}

void UBeamCli::RunCommandServer(UBeamCliCommand* Command, const TArray<FString>& Params, const FBeamOperationHandle& Op)
{
	// Ensure the CLI is installed
	if (!IsInstalled())
	{
		UE_LOG(LogBeamCli, Error, TEXT("CLI was not found locally. This system is not guaranteed to work because of this."));
		return;
	}

	// If we don't have a server up and running, first start one.
	if (CurrentCliServerUri.IsEmpty())
	{
		// Enqueue the Command 
		EnqueuedProcesses.Add(FBeamEnqueuedCliCommand(Command, Params, Op));

		// Set the URL to be "BEAM_WAITING_FOR_CLI_TO_START" so that future invocations of this don't start new instances of the CLIServer.
		CurrentCliServerUri = TEXT("BEAM_WAITING_FOR_CLI_TO_START");

		// Start the CLI server WITH prewarm.
		StartCliServer(false);
	}
	else if (CurrentCliServerUri == TEXT("BEAM_WAITING_FOR_CLI_TO_START"))
	{
		EnqueuedProcesses.Add(FBeamEnqueuedCliCommand(Command, Params, Op));
	}
	// If we do... just run it.
	else
	{
		RunningProcesses.Add(Command);
		Command->RunServer(CurrentCliServerUri, Params, Op);
	}
}

void UBeamCli::RunCommandSync(UBeamCliCommand* Command, const TArray<FString>& Params)
{
	Command->RunSync(Params);
	RunningProcesses.Add(Command);
}

void UBeamCli::OnCommandCompleted(UBeamCliCommand* Command)
{
	// The command can be null in the case of the process fail and this clean up being called more than once
	if (Command)
	{
		UE_LOG(LogBeamCli, Verbose, TEXT("[CLI] Clean up from running process: %s"), *Command->GetClass()->GetName());
	}
	RunningProcesses.Remove(Command);
}

void UBeamCli::StopCommand(UBeamCliCommand* Command)
{
	if (RunningProcesses.Remove(Command))
	{
		UE_LOG(LogBeamCli, Display, TEXT("Stopping running command. CMD=%s"), *Command->GetCommand())
		Command->Stop();
	}
}

FString UBeamCli::GetPathToCli() const
{
	return UBeamCliCommand::GetDotnetPath();
}
