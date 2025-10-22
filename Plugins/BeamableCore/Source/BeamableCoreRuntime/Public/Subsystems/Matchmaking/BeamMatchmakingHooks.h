// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamHookHandle.h"
#include "RequestTracker/BeamOperation.h"
#include "RequestTracker/BeamRequestTracker.h"
#include "UObject/Object.h"
#include "BeamMatchmakingHooks.generated.h"



UCLASS(BlueprintType, Blueprintable)
class UBeamMatchmakingHookHandle : public UBeamHookHandle
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, int32> PingsPerRegion;
};


/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class BEAMABLECORERUNTIME_API UBeamMatchmakingHooks : public UObject
{
	GENERATED_BODY()
	UWorld* GetWorld() const override
	{
		if (IsTemplate() || !GetOuter())
		{
			return nullptr;
		}
		return Context->GetWorld();
	}
	//
	const UObject* Context;
	
public:
	// UBeamMatchmakingHooks(const UObject* Context);

	void SetContext(const UObject* Context);
	
	UFUNCTION(BlueprintNativeEvent)
	void UpdatePings(UBeamMatchmakingHookHandle* MatchmakingHookHandle);
	virtual void UpdatePings_Implementation(UBeamMatchmakingHookHandle* MatchmakingHookHandle);

	UFUNCTION(BlueprintNativeEvent)
	void TryJoinQueue(FUserSlot Slot, FBeamContentId GameTypeQueue, FOptionalString Team, FOptionalArrayOfBeamTag Tags, FBeamOperationHandle Op);
	virtual void TryJoinQueue_Implementation(FUserSlot Slot, FBeamContentId GameTypeQueue, FOptionalString Team, FOptionalArrayOfBeamTag Tags, FBeamOperationHandle Op);

	UFUNCTION(BlueprintNativeEvent)
	void TryJoinQueueHookAction(UBeamMatchmakingHookHandle* MatchmakingHookHandle);
	virtual void TryJoinQueueHookAction_Implementation(UBeamMatchmakingHookHandle* MatchmakingHookHandle);
};
