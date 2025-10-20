// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RequestTracker/BeamOperation.h"
#include "UObject/Object.h"
#include "BeamMatchmakingHooks.generated.h"

UCLASS(BlueprintType)
class UBeamMatchmakingHookHandle : public UObject, public IBeamOperationEventData
{
	GENERATED_BODY()

public:
	const UObject* Context;
	UPROPERTY(BlueprintReadOnly)
	FBeamOperationHandle OperationHandle;
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

public:
	UFUNCTION(BlueprintNativeEvent)
	void UpdatePings(UBeamMatchmakingHookHandle* MatchmakingHookHandle);
	virtual void UpdatePings_Implementation(UBeamMatchmakingHookHandle* MatchmakingHookHandle);
};
