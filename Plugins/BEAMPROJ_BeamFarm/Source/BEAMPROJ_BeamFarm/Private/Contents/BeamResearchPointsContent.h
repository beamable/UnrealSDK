// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Content/BeamContentTypes/BeamCurrencyContent.h"

#include "BeamResearchPointsContent.generated.h"

/**
 * UBeamResearchPointsContent is the Beamable currency used to pay for research.
 * Content type ID: "research_points"
 *
 * Create content with ID "research_points.default" and publish to your realm.
 * The microservice deducts ResearchPointsCost (defined on each ResearchProjectContent)
 * from the player's balance when StartResearch is called.
 */
UCLASS(BlueprintType)
class BEAMPROJ_BEAMFARM_API UBeamResearchPointsContent : public UBeamCurrencyContent
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void GetContentType_UBeamResearchPointsContent(FString& Result) { Result = TEXT("research_points"); }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Research")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Research")
	FText Description;
};
