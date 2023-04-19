// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/BeamEditorSubsystem.h"
#include "BeamMicroservicesEditor.generated.h"

/**
 * 
 */
UCLASS()
class BEAMABLECOREEDITOR_API UBeamMicroservicesEditor : public UBeamEditorSubsystem
{
	GENERATED_BODY()

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	FDelegateHandle BeginPIE;
	FDelegateHandle EndPIE;
};
