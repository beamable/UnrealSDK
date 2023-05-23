// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/CLI/BeamCli.h"

#include "RequestTracker/BeamRequestTracker.h"
#include "Subsystems/BeamEditor.h"
#include "Subsystems/CLI/BeamCliCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliConfigCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliInitCommand.h"


FBeamOperationHandle UBeamCli::InitializeWhenEditorReady()
{
	// Try to run the CLI once just to see if it is installed. If Launch returns "true", that means the CLI was found in this machine's PATH. 
	IsInstalledCliProcess = MakeUnique<FMonitoredProcess>(UBeamCliCommand::PathToCli, TEXT("--help"), FPaths::ProjectDir(), true, true);
	IsInstalledCliProcess->OnOutput().BindLambda([](const FString& String)
	{
	});
	bInstalled = IsInstalledCliProcess->Launch();
	return Super::InitializeWhenEditorReady();
}

void UBeamCli::OnRealmInitialized()
{
	// Whenever we change realms, if the CLI is installed, we make sure it is pointing at the same realm we are in UE.  
	if (bInstalled)
	{
		const auto Cmd = NewObject<UBeamCliInitCommand>();
		Cmd->OnStreamOutput = [](const TArray<FBeamCliInitStreamData>& Stream, const TArray<int64>&, const FBeamOperationHandle&)
		{
			const auto Data = Stream.Last();
			UE_LOG(LogBeamCli, Display, TEXT("Initialized CLI with Unreal Project: %s %s %s"), *Data.host, *Data.cid, *Data.pid)
		};

		// Make sure the project is initialized with the locally signed in credentials in UE
		const auto Realm = GetDefault<UBeamCoreSettings>()->TargetRealm;
		const auto Host = GetDefault<UBeamCoreSettings>()->BeamableEnvironment->APIUrl;

		FBeamRealmUser EditorUserData;
		const auto Slot = Editor->GetMainEditorSlot(EditorUserData);

		RunCommandSync(Cmd, {
			               FString(TEXT("--host ") + Host),
			               FString(TEXT("--cid ") + Realm.Cid.AsString),
			               FString(TEXT("--pid ") + Realm.Pid.AsString),
			               FString(TEXT("--refresh-token ") + EditorUserData.AuthToken.RefreshToken),
			               FString(TEXT("--save-to-file")),
		               });
	}
}

void UBeamCli::RunCommand(UBeamCliCommand* Command, const TArray<FString>& Params, const FBeamOperationHandle& Op)
{
	Command->Run(Params, Op);
	RunningProcesses.Add(Command);
}

void UBeamCli::RunCommandSync(UBeamCliCommand* Command, const TArray<FString>& Params)
{
	Command->RunSync(Params);
	RunningProcesses.Add(Command);
}
