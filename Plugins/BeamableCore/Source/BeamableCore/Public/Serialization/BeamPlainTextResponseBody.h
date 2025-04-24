// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "UObject/Object.h"
#include "BeamPlainTextResponseBody.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamPlainTextResponseBody : public UObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Beam")
	FString Response;

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	UFUNCTION(BlueprintPure, Category="Beam|ResponseTypes", meta = (DisplayName="Plain Text String", CompactNodeTitle = "->", BlueprintAutocast))
	static FString Conv_BeamPlainTextResponseBodyToString(UBeamPlainTextResponseBody* Value) { return Value->Response; }	
};
