// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamOptionalTypes.h"

#include "BeamOptionalTypesLibrary.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamOptionalTypesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	 * @brief Constructs an FOptionalInt struct from the given value.	  
	 */
	UFUNCTION(BlueprintPure)
	static FOptionalInt MakeOptionalInt(const int& Value);

	UFUNCTION(BlueprintPure)
	static FOptionalString MakeOptionalString(const FString& Value);
};
