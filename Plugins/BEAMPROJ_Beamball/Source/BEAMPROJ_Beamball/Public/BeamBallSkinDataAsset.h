// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BeamBallSkinDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class BEAMPROJ_BEAMBALL_API UBeamBallSkinDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// Define a string for the skin item name
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	// Define a string for the skin item description
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemDescription;

	// Define a SoftObjectPath for the skin model
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<USkeletalMesh> ItemPath;
};
