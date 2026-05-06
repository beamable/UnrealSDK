// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Content/BeamContentTypes/BeamItemContent.h"
#include "BeamPlantData.h"

#include "BeamPlantContent.generated.h"

/**
 * BeamPlantContent represents a plantable crop in the Beamable content system.
 * This replaces the legacy FFarmCropData DataTable approach.
 * Uses shared FBeamPlantData structure for all plant properties.
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

	// All plant/crop data properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	FBeamPlantData PlantData;
};
