// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/BeamRuntimeSubsystem.h"
#include "HathoraSDK/Public/HathoraSDK.h"
#include "HathoraSDK/Public/HathoraTypes.h"

#include "BeamableHathora.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BEAMPROJ_BEAMBALL_API UBeamableHathora : public UBeamRuntimeSubsystem
{
	GENERATED_BODY()

private:
	TMap<FString, int32> PingsPerRegion;

public:

	UFUNCTION(BlueprintPure, BlueprintInternalUseOnly, meta=(DefaultToSelf="CallingContext"))
	static UBeamableHathora* GetSelf(const UObject* CallingContext) { return CallingContext->GetWorld()->GetGameInstance()->GetSubsystem<UBeamableHathora>(); }

	/**
	 * Refresh region ping latencies from Hathora.
	 * Retrieves current ping values for all available Hathora regions and updates the internal ping map.
	 */
	UFUNCTION(BlueprintCallable)
	FBeamOperationHandle RefreshPingsOperation(FBeamOperationEventHandler OnOperationEvent)
	{
		auto OperationHandler = Runtime->RequestTrackerSystem->BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);
		FHathoraSDK::Instance()->GetRegionalPings(FHathoraOnGetRegionalPings::CreateUObject(this, &UBeamableHathora::OnUpdateHathoraPings, OperationHandler));
		return OperationHandler;
	}
	/**
	 * @copydoc RefreshPingsOperation
	*/
	FBeamOperationHandle CPP_RefreshPingsOperation(FBeamOperationEventHandlerCode OnOperationEvent)
	{
		auto OperationHandler = Runtime->RequestTrackerSystem->CPP_BeginOperation({}, GetClass()->GetFName().ToString(), OnOperationEvent);
		FHathoraSDK::Instance()->GetRegionalPings(FHathoraOnGetRegionalPings::CreateUObject(this, &UBeamableHathora::OnUpdateHathoraPings, OperationHandler));
		return OperationHandler;
	}
	
	UFUNCTION(BlueprintCallable)
	void TryGetHathoraPings(TMap<FString, int32>& Pings)
	{
		Pings = PingsPerRegion; 
	}
	
	void OnUpdateHathoraPings(FHathoraRegionPings Pings, FBeamOperationHandle OperationHandler)
	{
		PingsPerRegion = Pings.Pings;

		Runtime->RequestTrackerSystem->TriggerOperationSuccess(OperationHandler, "Successfully updated pings");
	}

	
};
