// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Content/BeamContentObject.h"
#include "Farming/FarmTypes.h"

#include "BeamResearchProjectContent.generated.h"

/**
 * UBeamResearchProjectContent defines a research template in the Beamable content system.
 * Content type ID: "research_project"
 *
 * Each project specifies:
 *   - Which plant item type is consumed as the research subject (InputItemContentId)
 *   - How long research takes server-side (ResearchDurationSeconds)
 *   - What is granted on completion: a modifier, an item, or a currency (OutputType + OutputContentId + OutputQuantity)
 *
 * Examples:
 *   research_project.wheat_analysis  → InputItemContentId=itemplant.wheat,
 *                                       OutputType=Currency, OutputContentId=plant_raw_material.wheat_seed, OutputQuantity=4
 *   research_project.ancient_spore   → InputItemContentId=itemplant.ancient,
 *                                       OutputType=PlantModifier, OutputContentId=plant_modifier.spore_boost, OutputQuantity=1
 *
 * Create content with ID pattern "research_project.<name>" and publish to your realm.
 * Run `dotnet beam generate` after editing to regenerate Blueprint nodes.
 */
UCLASS(BlueprintType)
class BEAMPROJ_BEAMFARM_API UBeamResearchProjectContent : public UBeamContentObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void GetContentType_UBeamResearchProjectContent(FString& Result) { Result = TEXT("research_project"); }

	// Content ID of the plant item that must be submitted (itemplant.*).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Research")
	FString InputItemContentId;

	// Research points deducted from the player's balance when research starts.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Research", meta = (ClampMin = "1"))
	int32 ResearchPointsCost = 10;

	// How long (seconds) the research takes. Validated server-side.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Research", meta = (ClampMin = "1.0"))
	float ResearchDurationSeconds = 60.f;

	// What kind of reward is granted when research completes.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Research")
	EBeamResearchOutputType OutputType = EBeamResearchOutputType::PlantModifier;

	// Content ID of the reward (plant_modifier.*, itemplant.*, plant_raw_material.*, etc.).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Research")
	FString OutputContentId;

	// How many units of OutputContentId are granted on completion.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Research", meta = (ClampMin = "1"))
	int32 OutputQuantity = 1;

	// Human-readable name shown in the Research Lab UI.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Research")
	FText DisplayName;

	// Flavour text shown when inspecting this project.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Research")
	FText Description;
};
