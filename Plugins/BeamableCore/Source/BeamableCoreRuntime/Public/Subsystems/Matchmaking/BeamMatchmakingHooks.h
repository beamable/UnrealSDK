// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamHookHandle.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "RequestTracker/BeamOperation.h"
#include "RequestTracker/BeamRequestTracker.h"
#include "UObject/Object.h"
#include "BeamMatchmakingHooks.generated.h"



UCLASS(BlueprintType, Blueprintable)
class UBeamMatchmakingTryJoinQueueHookHandle : public UBeamHookHandle
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
	void UpdatePings(UBeamMatchmakingTryJoinQueueHookHandle* MatchmakingHookHandle);
	virtual void UpdatePings_Implementation(UBeamMatchmakingTryJoinQueueHookHandle* MatchmakingHookHandle);

	
	UFUNCTION(BlueprintNativeEvent)
	void PreTryJoinQueueHookAction(UBeamMatchmakingTryJoinQueueHookHandle* MatchmakingHookHandle);
	virtual void PreTryJoinQueueHookAction_Implementation(UBeamMatchmakingTryJoinQueueHookHandle* MatchmakingHookHandle);
	
	UFUNCTION(BlueprintNativeEvent)
	void TryJoinQueue(FUserSlot Slot, FBeamContentId GameTypeQueue, FOptionalString Team, FOptionalArrayOfBeamTag Tags, FBeamOperationHandle Op);
	virtual void TryJoinQueue_Implementation(FUserSlot Slot, FBeamContentId GameTypeQueue, FOptionalString Team, FOptionalArrayOfBeamTag Tags, FBeamOperationHandle Op);

	UFUNCTION(BlueprintNativeEvent)
	void AfterTryJoinQueueHookAction(UBeamMatchmakingTryJoinQueueHookHandle* MatchmakingHookHandle);
	virtual void AfterTryJoinQueueHookAction_Implementation(UBeamMatchmakingTryJoinQueueHookHandle* MatchmakingHookHandle);
};
