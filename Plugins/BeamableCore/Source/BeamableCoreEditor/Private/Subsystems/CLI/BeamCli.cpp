// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/CLI/BeamCli.h"

#include "RequestTracker/BeamRequestTracker.h"
#include "Subsystems/BeamEditor.h"
#include "Subsystems/CLI/BeamCliCommand.h"
#include "Subsystems/CLI/Autogen/BeamCliConfigCommand.h"


FBeamOperationHandle UBeamCli::InitializeWhenEditorReady()
{
	CliProcess = MakeUnique<FMonitoredProcess>(UBeamCliCommand::PathToCli, TEXT("--help"), FPaths::ProjectDir(), true,
	                                           true);
	CliProcess->OnOutput().BindLambda([](const FString& String)
	{
	});
	bInstalled = CliProcess->Launch();
	return Super::InitializeWhenEditorReady();
}

void UBeamCli::OnRealmInitialized()
{
	if (bInstalled)
	{
		const auto Cmd = NewObject<UBeamCliConfigCommand>();
		Cmd->OnStreamOutput = [](const TArray<FBeamCliConfigStreamData>& Stream, const TArray<int64>,
		                         const FBeamOperationHandle& BeamOperationHandle)
		{
			const auto Data = Stream.Last();
			UE_LOG(LogBeamCli, Display, TEXT("Initialized CLI with Unreal Project: %s %s %s"), *Data.host, *Data.cid,
			       *Data.pid)
		};

		// Make sure the project is initialized with the locally signed in credentials in UE
		const auto Realm = GetDefault<UBeamCoreSettings>()->TargetRealm;
		const auto Host = GetDefault<UBeamCoreSettings>()->BeamableEnvironment->APIUrl;

		FBeamRealmUser EditorUserData;
		const auto Slot = Editor->GetMainEditorSlot(EditorUserData);

		Cmd->Run({
			FString(TEXT("--host ") + Host),
			FString(TEXT("--cid ") + Realm.Cid.AsString),
			FString(TEXT("--pid ") + Realm.Pid.AsString),
			FString(TEXT("--refresh-token ") + EditorUserData.AuthToken.RefreshToken),
		});
		RunningProcesses.Add(Cmd);
	}
}

void UBeamCli::InitCommand()
{
	const auto Cmd = NewObject<UBeamCliConfigCommand>();

	Cmd->OnStreamOutput = [](const TArray<FBeamCliConfigStreamData>& Stream, const TArray<int64>,
	                         const FBeamOperationHandle& BeamOperationHandle)
	{
		FString JsonString;
		const auto Data = Stream.Last();
		if (FJsonObjectConverter::UStructToJsonObjectString(Data, JsonString))
		{
			UE_LOG(LogBeamCli, Warning, TEXT("STREAM MESSAGE CONVERTED!!!! %s"), *JsonString)
		}
	};
	Cmd->Run({});
	RunningProcesses.Add(Cmd);
}
