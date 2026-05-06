// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Content/BeamContentTypes/BeamCurrencyContent.h"
#include "BeamPlantData.h"
#include "BeamPlantRawMaterial.generated.h"

/**
 * BeamPlantRawMaterial represents a plantable crop as currency content.
 * Uses shared FBeamPlantData structure for all plant properties.
 */
UCLASS()
class BEAMPROJ_BEAMFARM_API UBeamPlantRawMaterial : public UBeamCurrencyContent
{
	GENERATED_BODY()

public:
	// Define the ContentTypeId for this Type
	UFUNCTION()
	void GetContentType_UBeamPlantRawMaterial(FString& Result) { Result = TEXT("plant.raw.material"); }
	
	// All plant/crop data properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	FBeamPlantData PlantData;
};
