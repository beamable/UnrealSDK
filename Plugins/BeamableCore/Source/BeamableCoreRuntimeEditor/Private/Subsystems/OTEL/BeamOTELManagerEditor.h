// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/BeamEditorSubsystem.h"
#include "BeamOTELManagerEditor.generated.h"

/**
 * 
 */
UCLASS()
class BEAMABLECORERUNTIMEEDITOR_API UBeamOTELManagerEditor : public UBeamEditorSubsystem
{
	GENERATED_BODY()

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	virtual FBeamOperationHandle OnRealmInitialized(FBeamRealmHandle NewRealm) override;
};
