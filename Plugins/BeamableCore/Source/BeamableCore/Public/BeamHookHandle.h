// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RequestTracker/BeamOperationHandle.h"
#include "UObject/Object.h"
#include "BeamHookHandle.generated.h"

/**
 * 
 */
UCLASS()
class BEAMABLECORE_API UBeamHookHandle : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	FBeamOperationHandle MainOperationHandle;
	
	UPROPERTY(BlueprintReadOnly)
	FBeamOperationHandle CurrentOperationHandle;

};
