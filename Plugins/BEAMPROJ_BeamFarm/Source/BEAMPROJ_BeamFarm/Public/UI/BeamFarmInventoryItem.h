// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamPlantData.h"
#include "PaperSprite.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "UObject/Object.h"
#include "BeamFarmInventoryItem.generated.h"


UENUM(BlueprintType)
enum EBeamFarmInventoryItemType
{
	RawPlant UMETA(DisplayName = "Raw Plant"),
	MutatedPlant UMETA(DisplayName = "Mutated Plant"),
};

/**
 * 
 */
USTRUCT(BlueprintType, Blueprintable)
struct BEAMPROJ_BEAMFARM_API FBeamFarmInventoryItem
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Inventory")
	FName ItemId;

	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Inventory")
	FText DisplayName;

	// The description of the item, shown in the inventory UI when the item is selected.
	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Inventory")
	FText Description;

	// The is selected state of the item, used to determine if the item is currently selected in the inventory UI.
	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Inventory")
	bool bIsSelected = false;

	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Inventory")
	TSoftObjectPtr<UPaperSprite> Icon;

	// The amount of this item in the player's inventory.
	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Inventory")
	int32 Quantity = 0;

	// Content ID for the item, used to link to the UBeamPlantContent for plant items.
	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Inventory")
	FBeamContentId ContentId;

	// Type of the inventory item, used to determine how to display it in the UI and what interactions are available.
	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Inventory")
	TEnumAsByte<EBeamFarmInventoryItemType> ItemType;

	// A list of properties for this item
	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Inventory")
	TMap<TEnumAsByte<EBeamFarmPropertyType>, int> Properties;
};
