// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "BeamBallRuntimeSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class BEAMPROJ_BEAMBALL_API UBeamBallRuntimeSubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

	public:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		Super::Initialize(Collection);
	}
};