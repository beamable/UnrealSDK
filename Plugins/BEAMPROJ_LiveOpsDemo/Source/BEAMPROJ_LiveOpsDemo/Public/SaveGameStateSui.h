// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UObject/Object.h"
#include "SaveGameStateSui.generated.h"

/**
 * 
 */
UCLASS()
class BEAMPROJ_LIVEOPSDEMO_API USaveGameStateSui : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = Basic)
	FString PrivateKey;

	UFUNCTION(BlueprintPure)
	static FString GetSlotName()
	{
		return "SlotName";
	}

	UFUNCTION(BlueprintPure)
	static int GetSlotIndex()
	{
		return 0;
	}
};
