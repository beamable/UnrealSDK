// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamCsvUtils.generated.h"

class UDataTable;

/**
 * 
 */
UCLASS()
class BEAMABLECORE_API UBeamCsvUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION()
	static void AddHeaderRow(FString& Csv, const TArray<FString> HeaderNames);

	UFUNCTION()
	static void AddAutoGenKeyField(FString& Csv);

	UFUNCTION()
	static void ParseIntoDataTable(UDataTable*& Table, UScriptStruct* StaticStruct, const FString& KeyField, const FString& Csv);
};
