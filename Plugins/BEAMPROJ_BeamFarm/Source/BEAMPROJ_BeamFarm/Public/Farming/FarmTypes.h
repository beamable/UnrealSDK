// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BeamSeedData.h"
#include "BeamPlantData.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "FarmTypes.generated.h"

class UPaperSprite;

// ─── Spawn zone types (used by UFarmCollectibleSpawner data and UBeamFarmSubsystem) ─────────────

UENUM(BlueprintType)
enum class EBeamFarmSpawnMode : uint8
{
	FixedTransforms UMETA(DisplayName = "Fixed Transforms"),
	WeightedZones UMETA(DisplayName = "Weighted Zones"),
};

USTRUCT(BlueprintType)
struct BEAMPROJ_BEAMFARM_API FBeamFarmSpawnZone
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone")
	FVector2D Center = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone", meta = (ClampMin = "1.0"))
	FVector2D HalfExtents = FVector2D(200.f, 200.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone", meta = (ClampMin = "0.0"))
	float Weight = 1.f;
};

USTRUCT(BlueprintType)
struct BEAMPROJ_BEAMFARM_API FBeamFarmExclusionZone
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone")
	FVector2D Center = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone", meta = (ClampMin = "1.0"))
	FVector2D HalfExtents = FVector2D(100.f, 100.f);
};

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
 * 3. Remove references to CropDataTable from character BP
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
	None UMETA(DisplayName = "None"),
	Farm UMETA(DisplayName = "Farm"),
	MutationLab UMETA(DisplayName = "Mutation Lab"),
	Research UMETA(DisplayName = "Research"),
	Delivery UMETA(DisplayName = "Delivery"),
};

UENUM(BlueprintType)
enum class EBeamFarmInventoryTab : uint8
{
	Crops UMETA(DisplayName = "Crops"),
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

USTRUCT(BlueprintType)
struct BEAMPROJ_BEAMFARM_API FBeamFarmMutationResult
{
	GENERATED_BODY()

	// Final properties of the plant item after all modifiers were applied.
	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Mutation")
	TMap<FString, FString> NewProperties;

	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Mutation")
	FString Message;
};

USTRUCT(BlueprintType)
struct BEAMPROJ_BEAMFARM_API FBeamFarmGroundItemParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|GroundItem")
	FString GroundItemId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|GroundItem")
	FString ContentId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|GroundItem")
	int32 Quantity = 1;

	// "RawMaterial" or "PlantItem"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|GroundItem")
	FString ItemType;
};

USTRUCT(BlueprintType)
struct BEAMPROJ_BEAMFARM_API FBeamFarmCollectibleInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Collectible")
	FString ContentId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Collectible")
	int32 Quantity = 1;

	// Populated for RawMaterial items
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Collectible")
	FBeamSeedData SeedData;

	// Populated for PlantItem items
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Collectible")
	FBeamPlantData PlantData;

	// "RawMaterial" or "PlantItem"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Collectible")
	FString ItemType;
};

// ─── Delivery system ───────────────────────────────────────────────────────────────────────────

// How a delivery requirement compares an item property value against a threshold.
// Values use BEAM_ prefix so EnumToSerializationName produces "GreaterThan"/"LowerThan".
UENUM(BlueprintType)
enum class EBeamDeliveryComparison : uint8
{
	BEAM_GreaterThan UMETA(DisplayName = "Greater Than"),
	BEAM_LowerThan UMETA(DisplayName = "Lower Than"),
};

// A single property rule an item must satisfy to fulfil a delivery order.
// Maps to DeliveryRequirement in BeamFarmMs.Delivery.cs.
USTRUCT(BlueprintType)
struct BEAMPROJ_BEAMFARM_API FBeamDeliveryRequirement : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	// Property name to inspect — must match EBeamFarmPropertyType names
	// (e.g. "Corrosive", "Mutagenic", "Radioactive").
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Delivery")
	FString PropertyName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Delivery")
	EBeamDeliveryComparison Comparison = EBeamDeliveryComparison::BEAM_GreaterThan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Delivery")
	int32 Value = 0;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("PropertyName"), PropertyName);
		const FString CompStr = UBeamJsonUtils::EnumToSerializationName<EBeamDeliveryComparison>(Comparison);
		Serializer->WriteValue(TEXT("Comparison"), CompStr);
		Serializer->WriteValue(TEXT("Value"), Value);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("PropertyName"), Bag, PropertyName);
		FString CompStr;
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Comparison"), Bag, CompStr);
		Comparison = UBeamJsonUtils::SerializationNameToEnum<EBeamDeliveryComparison>(CompStr);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Value"), Bag, Value);
	}
};

// Full description of an active delivery order, populated from server response.
// Passed through OnDeliveryOrdersReceived and displayed by UBeamFarmDeliveryWidget.
USTRUCT(BlueprintType)
struct BEAMPROJ_BEAMFARM_API FBeamDeliveryOrderInfo
{
	GENERATED_BODY()

	// Content ID of the delivery_order.* content that generated this slot.
	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Delivery")
	FString OrderId;

	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Delivery")
	FString DisplayName;

	// Content ID of the plant item type that must be delivered (itemplant.*).
	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Delivery")
	FString RequiredItemContentId;

	// Property rules the delivered item instance must satisfy.
	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Delivery")
	TArray<FBeamDeliveryRequirement> Requirements;

	// Beamable currency content ID rewarded on delivery (e.g. "currency.crystals").
	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Delivery")
	FString RewardCurrencyId;

	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Delivery")
	int32 RewardAmount = 0;
};

// ─── Slot interaction request ──────────────────────────────────────────────────────────────────
// Passed to UBeamFarmSubsystem::HandleSlotInteraction. Carries only slot-side data;
// the subsystem reads its own selection state (SelectedCrop, SelectedCropContentId).

USTRUCT(BlueprintType)
struct BEAMPROJ_BEAMFARM_API FBeamFarmInteractionRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Farming")
	FString SlotId;

	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Farming")
	EFarmSlotState SlotState = EFarmSlotState::Empty;

	// Data of the seed currently planted in the slot (valid for Growing / ReadyToHarvest).
	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Farming")
	FBeamSeedData PlantedSeed;
};
