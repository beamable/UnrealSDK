// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/CLI/BeamCli.h"

#include "HttpModule.h"
#include "RequestTracker/BeamRequestTracker.h"
#include "Subsystems/BeamEditor.h"
#include "Subsystems/CLI/BeamCliCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliInitCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliServerServeCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliVersionCommand.h"


FBeamOperationHandle UBeamCli::InitializeWhenEditorReady()
{
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
	IsInstalledProcess = MakeUnique<FMonitoredProcess>(UBeamCliCommand::PathToLocalCli, TEXT("beam version"), FPaths::ProjectDir(), true, true);
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
				RequestTracker->TriggerOperationSuccess(Op, CurrentCliServerUri);				
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
		UE_LOG(LogBeamCli, Verbose, TEXT("No local CLI version installed."));
		bInstalled = FOptionalBool{false};
	}

	// If we couldn't find either version, we return a failed op instead.
	if (bInstalled.IsSet && !bInstalled.Val)
	{
		const auto NoCliErr = FString::Printf(TEXT("Beam CLI not found. Please make sure you have an installed Beamable CLI (Version: %s)"), *DotnetTools);
		RequestTracker->TriggerOperationError(Op, NoCliErr);
	}

	return Op;
}

FBeamOperationHandle UBeamCli::InitializeRealm(FBeamRealmHandle NewRealm)
{
	FBeamRealmUser EditorUserData;
	const auto Slot = Editor->GetMainEditorSlot(EditorUserData);

	if (IsInstalled())
	{
		// Make sure the project is initialized with the locally signed in credentials in UE
		const auto Realm = GetDefault<UBeamCoreSettings>()->TargetRealm;
		const auto Host = GetDefault<UBeamCoreSettings>()->BeamableEnvironment->APIUrl;

		const auto Op = RequestTracker->CPP_BeginOperation({Slot}, GetName(), {});
		const auto Cmd = NewObject<UBeamCliInitCommand>();
		Cmd->OnStreamOutput = [this, Op](const TArray<UBeamCliInitStreamData*>& Stream, const TArray<int64>&, const FBeamOperationHandle&)
		{
			const auto Data = Stream.Last();
			RequestTracker->TriggerOperationSuccess(Op, {});
			UE_LOG(LogBeamCli, Display, TEXT("Initialized CLI with Unreal Project: %s %s %s"), *Data->Host, *Data->Cid, *Data->Pid)
		};

		RunCommandServer(Cmd, {
			                 FString(TEXT("--host ") + Host),
			                 FString(TEXT("--cid ") + Realm.Cid.AsString),
			                 FString(TEXT("--pid ") + Realm.Pid.AsString),
			                 FString(TEXT("--refresh-token ") + EditorUserData.AuthToken.RefreshToken)
		                 }, Op);

		return Op;
	}

	UE_LOG(LogBeamCli, Error, TEXT("CLI not installed or not detected. Please make sure you have the CLI installed!"))
	return RequestTracker->CPP_BeginErrorOperation({Slot}, GetName(), TEXT("CLI not installed or not detected. Please make sure you have the CLI installed!"), {});
}

void UBeamCli::StartCliServer(FBeamOperationHandle Op)
{
	const auto ServerCmd = NewObject<UBeamCliServerServeCommand>();
	ServerCmd->OnStreamOutput = [this, Op](const TArray<UBeamCliServerServeStreamData*>& Stream, const TArray<int64>&, const FBeamOperationHandle&)
	{
		CurrentCliServerUri = Stream[0]->Uri;

		// Complete the given operation
		if (RequestTracker->ActiveOperations.Contains(Op) && RequestTracker->ActiveOperationState[Op]->Status == 0)
			RequestTracker->TriggerOperationSuccess(Op, CurrentCliServerUri);

		UE_LOG(LogBeamCli, Display, TEXT("SERVER CLI STARTED. PORT=%d, URI=%s"), Stream[0]->Port, *Stream[0]->Uri)
	};

	ServerCmd->OnCompleted = [this](const int& ResCode, const FBeamOperationHandle&)
	{
		CurrentCliServerUri = TEXT("");
		UE_LOG(LogBeamCli, Display, TEXT("On SERVER CLI TERMINATED %d"), ResCode)
	};

	RunCommand(ServerCmd, {TEXT("-d 300")}, {});
}

void UBeamCli::RunCommand(UBeamCliCommand* Command, const TArray<FString>& Params, const FBeamOperationHandle& Op)
{
	Command->Run(Params, Op);
	RunningProcesses.Add(Command);
}

void UBeamCli::RunCommandServer(UBeamCliCommand* Command, const TArray<FString>& Params, const FBeamOperationHandle& Op)
{
	// First, we add the command to the list of running commands, so that we don't get it garbage collected in the case where we have to wait for the server to boot up.
	RunningProcesses.Add(Command);

	// If we don't have a server up and running, first start one.
	if (CurrentCliServerUri.IsEmpty())
	{
		// Run the server command so we boot the server up --- when its up, run the intended command.
		auto ServerStartHandler = FBeamOperationEventHandlerCode::CreateLambda([this, Command, Params, Op](FBeamOperationEvent Evt)
		{
			if (Evt.EventType == OET_SUCCESS)
			{
				UE_LOG(LogBeamCli, Display, TEXT("Now executing command. CMD=%s"), *Command->GetClass()->GetName());
				Command->RunServer(CurrentCliServerUri, Params, Op);
			}
			else
			{
				UE_LOG(LogBeamCli, Error, TEXT("Should not be seeing this. If you do see it, please report a bug to Beamable. CMD=%s"), *Command->GetClass()->GetName());
			}
		});
		const auto ServerStartOp = RequestTracker->CPP_BeginOperation({}, GetName(), ServerStartHandler);
		StartCliServer(ServerStartOp);
	}
	// If we do... just run it.
	else
	{
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
	RunningProcesses.Remove(Command);
}

void UBeamCli::StopCommand(UBeamCliCommand* Command)
{	
	if(RunningProcesses.Remove(Command))
	{
		Command->Stop();
	}
}

FString UBeamCli::GetPathToCli() const
{
	check(IsInstalled())
	return UBeamCliCommand::PathToLocalCli;
}
