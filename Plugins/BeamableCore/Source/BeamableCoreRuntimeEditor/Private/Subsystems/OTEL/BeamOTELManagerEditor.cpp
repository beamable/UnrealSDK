// Fill out your copyright notice in the Description page of Project Settings.


#include "BeamOTELManagerEditor.h"

#include "Subsystems/CLI/Autogen/BeamCliTelemetryPruneCommand.h"

void UBeamOTELManagerEditor::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

FBeamOperationHandle UBeamOTELManagerEditor::OnRealmInitialized(FBeamRealmHandle NewRealm)
{
	UBeamCliTelemetryPruneCommand* PruneCommand = NewObject<UBeamCliTelemetryPruneCommand>();
	
	auto Cli = GEditor->GetEditorSubsystem<UBeamCli>();
	
	Cli->RunCommand(PruneCommand, {TEXT("--delete-all")}, {});

	return Super::OnRealmInitialized(NewRealm);
}
