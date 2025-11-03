// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamHookHandle.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "Hooks/BeamBaseHook.h"
#include "RequestTracker/BeamOperation.h"
#include "UObject/Object.h"
#include "BeamMatchmakingHooks.generated.h"


struct FOptionalString;

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
class BEAMABLECORERUNTIME_API UBeamMatchmakingHooks : public UBeamBaseHook
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent)
	void PreTryJoinQueue(UBeamHookHandle* MatchmakingHookHandle);
	virtual void PreTryJoinQueue_Implementation(UBeamHookHandle* MatchmakingHookHandle);

	UFUNCTION(BlueprintNativeEvent)
	void TryJoinQueue(FUserSlot Slot, FBeamContentId GameTypeQueue, FOptionalString Team, FOptionalArrayOfBeamTag Tags, FBeamOperationHandle Op);
	virtual void TryJoinQueue_Implementation(FUserSlot Slot, FBeamContentId GameTypeQueue, FOptionalString Team, FOptionalArrayOfBeamTag Tags, FBeamOperationHandle Op);
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class BEAMABLECORERUNTIME_API UBeamDefaultMatchmakingHooks : public UBeamMatchmakingHooks
{
	GENERATED_BODY()

public:
	
	virtual void TryJoinQueue_Implementation(FUserSlot Slot, FBeamContentId GameTypeQueue, FOptionalString Team, FOptionalArrayOfBeamTag Tags, FBeamOperationHandle Op) override;
};

