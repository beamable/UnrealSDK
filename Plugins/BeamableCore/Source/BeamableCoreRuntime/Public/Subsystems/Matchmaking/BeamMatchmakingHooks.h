// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hooks/BeamBaseHook.h"
#include "RequestTracker/BeamOperation.h"
#include "RequestTracker/BeamOperationHandle.h"
#include "BeamMatchmakingHooks.generated.h"

UCLASS(BlueprintType)
class UBeamMatchmakingHookHandle : public UObject, public IBeamOperationEventData
{
	GENERATED_BODY()

public:
	const UObject* Context;
	UPROPERTY(BlueprintReadWrite)
	FBeamOperationHandle OperationHandle;
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, int32> PingsPerRegion;
};

/**
 * 
 */
UCLASS()
class BEAMABLECORERUNTIME_API UBeamMatchmakingHooks : public UBeamBaseHook
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void UpdatePings(UBeamMatchmakingHookHandle* MatchmakingHookHandle);
	virtual void UpdatePings_Implementation(UBeamMatchmakingHookHandle* MatchmakingHookHandle);
};
