// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamOTELManagerEditor.h"

#include "Subsystems/CLI/Autogen/BeamCliTelemetryPushCommand.h"

void UBeamOTELManagerEditor::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

FBeamOperationHandle UBeamOTELManagerEditor::OnRealmInitialized(FBeamRealmHandle NewRealm)
{
	UBeamCliTelemetryPushCommand* PushCommand = NewObject<UBeamCliTelemetryPushCommand>();
	
	auto Cli = GEditor->GetEditorSubsystem<UBeamCli>();
	
	Cli->RunCommand(PushCommand, {TEXT("-q")}, {});

	return Super::OnRealmInitialized(NewRealm);
}

void UBeamOTELManagerEditor::AddLog(FString Message, FString StackTrace, FString OtelLogLevel)
{
}

void UBeamOTELManagerEditor::OtelPruneLogs()
{
}

void UBeamOTELManagerEditor::PublishLogs()
{
}
