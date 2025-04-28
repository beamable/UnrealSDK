// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BeamBallListingDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class BEAMPROJ_BEAMBALL_API UBeamBallListingDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// Define a string for the item name
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	// Define a SoftObjectPath for the item icon
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;
};
