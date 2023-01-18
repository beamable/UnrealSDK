// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BeamCsvUtils.generated.h"

class UDataTable;

DECLARE_STATS_GROUP(TEXT("BeamUtils"), STATGROUP_BeamUtils, STATCAT_RequestDeserialization)



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

	template <class T>
	static void StoreNameAsColumn(UDataTable* Table, FString ColumnName)
	{
		DECLARE_SCOPE_CYCLE_COUNTER(TEXT("UBeamCsvUtils.StoreNameAsColumn"), STATID_StoreNameAsColumn, STATGROUP_BeamUtils)
		
		const auto RowNames= Table->GetRowNames();

		const UStruct* StructType = T::StaticStruct();	
		const auto Field = StructType->FindPropertyByName(FName(ColumnName));

		// If we ever run into perf problems with large manifests, we can split this into multiple tasks and just go wide
		if (const FStrProperty* StrProperty = CastField<const FStrProperty>(Field))
		{
			TArray<T*> AllRows;	
			Table->GetAllRows(TEXT(""), AllRows);
			for (auto i = 0; i < AllRows.Num(); i++)
			{
				const auto RowName = RowNames[i].ToString();
				if(FString* ValuePtr = StrProperty->ContainerPtrToValuePtr<FString>(AllRows[i]))
				{
					*ValuePtr = RowName;
				}				
			} 		
		}
			
	}
};
