// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Content/BeamContentTypes/BeamCurrencyContent.h"
#include "SuiGameCoins.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class BEAMPROJ_LIVEOPSDEMO_API USuiGameCoins : public UBeamCurrencyContent
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void GetContentType_USuiGameCoins(FString& Result){ Result = TEXT("game_coin"); }

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName name;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString symbol;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 decimals;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString image;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString description;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int64 initialSupply;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool allowSpending;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString allowBuying;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString allowTransfers;
};
