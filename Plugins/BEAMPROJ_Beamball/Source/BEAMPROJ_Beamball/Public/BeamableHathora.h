// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HathoraSDK.h"
#include "HathoraTypes.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "BeamableHathora.generated.h"

/**
 * 
 */
UCLASS()
class BEAMPROJ_BEAMBALL_API UBeamableHathora : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

	TMap<FString, int32> PingsPerRegion;

public:

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamableHathora* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamableHathora>(); }
	
	FBeamOperationHandle RefreshPingsOperation(FBeamOperationEventHandler Operation)
	{
		auto OperationHandler = Runtime->RequestTrackerSystem->BeginOperation({}, GetClass()->GetFName().ToString(), Operation);
		FHathoraSDK::Instance()->GetRegionalPings(FHathoraOnGetRegionalPings::CreateLambda(this, &UBeamableHathora::OnUpdateHathoraPings, OperationHandler));
		return OperationHandler;
	}

	FBeamOperationHandle CPP_RefreshPingsOperation(FBeamOperationEventHandlerCode Operation)
	{
		auto OperationHandler = Runtime->RequestTrackerSystem->CPP_BeginOperation({}, GetClass()->GetFName().ToString(), Operation);
		FHathoraSDK::Instance()->GetRegionalPings(FHathoraOnGetRegionalPings::CreateLambda(this, &UBeamableHathora::OnUpdateHathoraPings, OperationHandler));
		return OperationHandler;
	}
	
	void TryGetHathoraPings(TMap<FString, int32>& Pings)
	{
		PingsPerRegion = Pings; 
	}
	
	void OnUpdateHathoraPings(FHathoraRegionPings Pings, FBeamOperationHandle OperationHandler)
	{
		PingsPerRegion = Pings.Pings;

		Runtime->RequestTrackerSystem->TriggerOperationSuccess(OperationHandler, "Successfully updated pings");
	}

	
};
