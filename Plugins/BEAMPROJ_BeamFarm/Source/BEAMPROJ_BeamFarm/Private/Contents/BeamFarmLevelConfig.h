// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Content/BeamContentObject.h"

#include "BeamFarmLevelConfig.generated.h"

/**
 * Singleton configuration for the player level progression system.
 * Content type ID: "farm_level_config"
 *
 * Publish one entry with content ID "farm_level_config.default".
 *
 * XpThresholds[i] = total XP required to reach level (i+1).
 * Example: { 100, 300, 600, 1000 } means level 0→1 costs 100 total XP,
 * level 1→2 costs 300 total XP, etc.
 */
UCLASS(BlueprintType)
class BEAMPROJ_BEAMFARM_API UBeamFarmLevelConfig : public UBeamContentObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void GetContentType_UBeamFarmLevelConfig(FString& Result) { Result = TEXT("farm_level_config"); }

	// Total XP required to reach each level boundary. Index 0 = level 1, index 1 = level 2, etc.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Level")
	TArray<int32> XpThresholds = { 100, 300, 600, 1000, 1500, 2200, 3000, 4000, 5500, 7500 };

	// XP granted when a harvest is collected.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Level", meta = (ClampMin = "0"))
	int32 XpPerHarvest = 10;

	// XP granted when a ground collectible is picked up.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Level", meta = (ClampMin = "0"))
	int32 XpPerGroundCollect = 5;

	// XP granted when a delivery order is fulfilled.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Level", meta = (ClampMin = "0"))
	int32 XpPerDelivery = 25;

	// XP granted when research is collected.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Level", meta = (ClampMin = "0"))
	int32 XpPerResearch = 50;
};
