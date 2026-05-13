// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FarmTypes.generated.h"

class UPaperSprite;

UENUM(BlueprintType)
enum class EFarmSlotState : uint8
{
	Empty UMETA(DisplayName = "Empty"),
	Growing UMETA(DisplayName = "Growing"),
	ReadyToHarvest UMETA(DisplayName = "Ready To Harvest"),
};

UENUM(BlueprintType)
enum class EFarmingInteractionState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Planting UMETA(DisplayName = "Planting"),
};

/**
 * DEPRECATED: FFarmCropData is deprecated in favor of UBeamPlantContent.
 * 
 * The farming system now uses UBeamPlantContent (itemplant content type) instead of DataTables.
 * This struct is kept for backward compatibility only.
 * 
 * Migration:
 * 1. Create UBeamPlantContent assets using Beamable content tools
 * 2. Set the same properties in UBeamPlantContent
 * 3. Remove references to CropDataTable from UFarmingComponent
 * 4. Use GetAllPlants() and FindPlantBySeedId() instead
 */
USTRUCT(BlueprintType, meta = (DeprecatedNode, DeprecationMessage = "Use UBeamPlantContent instead"))
struct BEAMPROJ_BEAMFARM_API FFarmCropData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Crop")
	FName CropId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Crop")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Crop")
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Crop", meta = (ClampMin = "1.0"))
	float GrowTimeSeconds = 30.f;

	// Shown on the slot while the crop is growing.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Crop")
	TObjectPtr<UPaperSprite> GrowingSprite;

	// Shown on the slot when the crop is ready to harvest.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Crop")
	TObjectPtr<UPaperSprite> ReadyToHarvestSprite;

	// Beamable content ID of the seed item consumed from inventory when planting (e.g. "items.wheat_seed")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Crop")
	FString SeedItemContentId;

	// Beamable content ID of the item added to inventory on harvest (e.g. "items.wheat")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Crop")
	FString HarvestItemContentId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Crop", meta = (ClampMin = "1"))
	int32 HarvestYield = 1;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFarmSlotStateChangedDelegate, class AFarmSlotActor*, Slot, EFarmSlotState, NewState);

UENUM(BlueprintType)
enum class EBeamFarmBuildingType : uint8
{
	None        UMETA(DisplayName = "None"),
	Farm        UMETA(DisplayName = "Farm"),
	MutationLab UMETA(DisplayName = "Mutation Lab"),
	Shop        UMETA(DisplayName = "Shop"),
	Upgrades    UMETA(DisplayName = "Upgrades"),
};

UENUM(BlueprintType)
enum class EBeamFarmInventoryTab : uint8
{
	Crops     UMETA(DisplayName = "Crops"),
	Materials UMETA(DisplayName = "Materials"),
};

USTRUCT(BlueprintType)
struct BEAMPROJ_BEAMFARM_API FBeamFarmMutationInput
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Mutation")
	FString ItemContentId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Mutation")
	int32 Quantity = 1;
};

USTRUCT(BlueprintType)
struct BEAMPROJ_BEAMFARM_API FBeamFarmMutationOutput
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Mutation")
	FString ItemContentId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Mutation")
	int32 Quantity = 0;
};
