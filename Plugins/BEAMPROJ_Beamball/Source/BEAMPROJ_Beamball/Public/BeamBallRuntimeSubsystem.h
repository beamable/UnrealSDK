// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamBallHathoraUtility.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "Subsystems/Stats/BeamStatsSubsystem.h"
#include "BeamBallRuntimeSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class BEAMPROJ_BEAMBALL_API UBeamBallRuntimeSubsystem : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

	UBeamStatsSubsystem* Stats;
	
	public:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override
	{
		Super::Initialize(Collection);
		
		Stats = Collection.InitializeDependency<UBeamStatsSubsystem>();
	}

	/**
	 * @brief Refreshes the stats the user at the given user slot. 
	 */
	UFUNCTION(BlueprintCallable, Category="BeamBall", meta=(DefaultToSelf="CallingContext", AdvancedDisplay="CallingContext"))
	FBeamOperationHandle RefreshHathoraPingStatOperation(FUserSlot UserSlot, FBeamOperationEventHandler OnOperationEvent){
		const auto Handle = Runtime->RequestTrackerSystem->BeginOperation({UserSlot}, GetClass()->GetFName().ToString(), OnOperationEvent);
		BeamBallHathoraUtility::HathoraPingsOperation(UserSlot, Runtime, Stats, Handle);
		return Handle;
	}

	
	
};