// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamHookHandle.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "Hooks/BeamBaseHook.h"
#include "RequestTracker/BeamOperation.h"
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
class BEAMABLECORERUNTIME_API UBeamMatchmakingUpdatePingHook : public UBeamBaseHook
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void UpdatePings(UBeamMatchmakingTryJoinQueueHookHandle* MatchmakingHookHandle);
	virtual void UpdatePings_Implementation(UBeamMatchmakingTryJoinQueueHookHandle* MatchmakingHookHandle);

};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class BEAMABLECORERUNTIME_API UBeamMatchmakingTryJoinQueueHook : public UBeamBaseHook
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent)
	void TryJoinQueue(FUserSlot Slot, FBeamContentId GameTypeQueue, FOptionalString Team, FOptionalArrayOfBeamTag Tags, FBeamOperationHandle Op);
	virtual void TryJoinQueue_Implementation(FUserSlot Slot, FBeamContentId GameTypeQueue, FOptionalString Team, FOptionalArrayOfBeamTag Tags, FBeamOperationHandle Op);

};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class BEAMABLECORERUNTIME_API UBeamMatchmakingPreTryJoinQueueHook : public UBeamBaseHook
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent)
	void PreTryJoinQueueHookAction(UBeamMatchmakingTryJoinQueueHookHandle* MatchmakingHookHandle);
	virtual void PreTryJoinQueueHookAction_Implementation(UBeamMatchmakingTryJoinQueueHookHandle* MatchmakingHookHandle);

	UFUNCTION(BlueprintNativeEvent)
	void PreTryJoinQueueHookActionParallel(FBeamOperationHandle OperationHandle);
	virtual void PreTryJoinQueueHookActionParallel_Implementation(FBeamOperationHandle MatchmakingHookHandle);
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class BEAMABLECORERUNTIME_API UBeamMatchmakingAfterTryJoinQueueHook : public UBeamBaseHook
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent)
	void AfterTryJoinQueueHookAction(UBeamMatchmakingTryJoinQueueHookHandle* MatchmakingHookHandle);
	virtual void AfterTryJoinQueueHookAction_Implementation(UBeamMatchmakingTryJoinQueueHookHandle* MatchmakingHookHandle);

	UFUNCTION(BlueprintNativeEvent)
	void AfterTryJoinQueueHookActionParallel(FBeamOperationHandle MatchmakingHookHandle);
	virtual void AfterTryJoinQueueHookActionParallel_Implementation(FBeamOperationHandle MatchmakingHookHandle);
};
