// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Content/BeamContentTypes/BeamCurrencyContent.h"
#include "BeamSeedData.h"
#include "BeamSeedsContent.generated.h"

/**
 * BeamSeedsContent represents seed items that can be planted on farm slots.
 * Uses FBeamSeedData for inventory display and planting properties.
 */
UCLASS()
class BEAMPROJ_BEAMFARM_API UBeamSeedsContent : public UBeamCurrencyContent
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void GetContentType_UBeamSeedsContent(FString& Result) { Result = TEXT("plant_raw_material"); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Seed")
	FBeamSeedData SeedData;
};
