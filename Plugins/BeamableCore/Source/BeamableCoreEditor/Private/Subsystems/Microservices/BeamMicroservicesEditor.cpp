// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/Microservices/BeamMicroservicesEditor.h"

#include "BeamLogging.h"
#include "BeamBackend/BeamMicroserviceClientSubsystem.h"

void UBeamMicroservicesEditor::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	BeginPIE = FEditorDelegates::BeginPIE.AddLambda([](bool Cond)
	{
		const auto asd = GEngine->GetEngineSubsystemArray<UBeamMicroserviceClientSubsystem>();
		for (UBeamMicroserviceClientSubsystem* Asd : asd)
		{
			Asd->Prefix = FPlatformProcess::ComputerName();
			UE_LOG(LogBeamMicroservices, Display, TEXT("%s"), *Asd->Prefix)
		}
	});

	EndPIE = FEditorDelegates::EndPIE.AddLambda([](bool Cond)
	{
		const auto asd = GEngine->GetEngineSubsystemArray<UBeamMicroserviceClientSubsystem>();
		for (UBeamMicroserviceClientSubsystem* Asd : asd)
		{
			Asd->Prefix = TEXT("");
		}
	});
}

void UBeamMicroservicesEditor::Deinitialize()
{
	Super::Deinitialize();
	FEditorDelegates::BeginPIE.Remove(BeginPIE);
	FEditorDelegates::EndPIE.Remove(EndPIE);
}
