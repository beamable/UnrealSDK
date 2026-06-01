// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Content/BeamContentTypes/BeamItemContent.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "BeamPlantData.h"
#include "Farming/FarmTypes.h"

#include "BeamPlantContent.generated.h"

/**
 * BeamPlantContent represents a plantable crop in the Beamable content system.
 * Content type ID: "itemplant"
 *
 * Plant items can optionally be researched in the Research Lab. Set bCanBeResearched = true
 * and fill in the Research section fields to enable research for a plant type.
 */
UCLASS(BlueprintType)
class BEAMPROJ_BEAMFARM_API UBeamPlantContent : public UBeamItemContent
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void GetContentType_UBeamPlantContent(FString& Result) { Result = TEXT("itemplant"); }

	// ─── Farming ──────────────────────────────────────────────────────────────

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	FBeamPlantData PlantData;

	// ─── Research ─────────────────────────────────────────────────────────────

	// Whether this plant type can be submitted for research in the Research Lab.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Research")
	bool bCanBeResearched = false;

	// Research points deducted from the player's balance when research starts.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Research", meta = (ClampMin = "0", EditCondition = "bCanBeResearched"))
	int32 ResearchPointsCost = 10;

	// How long (seconds) the research takes. Validated server-side.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Research", meta = (ClampMin = "1.0", EditCondition = "bCanBeResearched"))
	float ResearchDurationSeconds = 60.f;

	// What kind of reward is granted when research completes.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Research", meta = (EditCondition = "bCanBeResearched"))
	EBeamResearchOutputType ResearchOutputType = EBeamResearchOutputType::PlantModifier;

	// Content ID of the reward (plant_modifier.*, itemplant.*, plant_raw_material.*, etc.).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Research", meta = (EditCondition = "bCanBeResearched"))
	FBeamContentId ResearchOutputContentId;

	// How many units of ResearchOutputContentId are granted on completion.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Research", meta = (ClampMin = "1", EditCondition = "bCanBeResearched"))
	int32 ResearchOutputQuantity = 1;
};
