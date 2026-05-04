// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Content/BeamContentTypes/BeamItemContent.h"
#include "PaperSprite.h"

#include "BeamPlantContent.generated.h"

/**
 * BeamPlantContent represents a plantable crop in the Beamable content system.
 * This replaces the legacy FFarmCropData DataTable approach.
 * 
 * To create plant content:
 * 1. In Unreal Editor, use Beamable Content tools to create new "itemplant" content
 * 2. Set all crop properties (grow time, sprites, seed/harvest item IDs)
 * 3. Publish content to your realm
 */
UCLASS(BlueprintType)
class BEAMPROJ_BEAMFARM_API UBeamPlantContent : public UBeamItemContent
{
	GENERATED_BODY()

public:
	// Define the ContentTypeId for this Type
	UFUNCTION()
	void GetContentType_UBeamPlantContent(FString& Result) { Result = TEXT("itemplant"); }

	// Display name shown in UI (e.g., "Wheat", "Corn")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	FText DisplayName;

	// Icon for inventory/UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	TSoftObjectPtr<UTexture2D> Icon;

	// Time in seconds for the crop to grow from planting to harvest
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant", meta = (ClampMin = "1.0"))
	float GrowTimeSeconds = 30.f;

	// Sprite shown on the farm slot while the crop is growing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	TSoftObjectPtr<UPaperSprite> GrowingSprite;

	// Sprite shown on the farm slot when the crop is ready to harvest
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	TSoftObjectPtr<UPaperSprite> ReadyToHarvestSprite;

	// Beamable content ID of the seed item consumed from inventory when planting
	// Example: "items.wheat_seed"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	FString SeedItemContentId;

	// Beamable content ID of the item added to inventory on harvest
	// Example: "items.wheat"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	FString HarvestItemContentId;

	// Number of items to add to inventory when harvested
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant", meta = (ClampMin = "1"))
	int32 HarvestYield = 1;
};
