// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeamPlantData.h"
#include "Farming/FarmTypes.h"
#include "PaperSprite.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/Object.h"
#include "BeamFarmInventoryItem.generated.h"


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
	TEnumAsByte<EBeamFarmItemType> ItemType;

	// A list of properties for this item
	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Inventory")
	TMap<TEnumAsByte<EBeamFarmPropertyType>, int> Properties;

	// ─── Research ─────────────────────────────────────────────────────────────

	// True when this item instance has an active research job (has "research_started_at" property).
	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Research")
	bool bIsInResearch = false;

	// Unix UTC timestamp (seconds) when research started. 0 if not in research.
	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Research")
	int64 ResearchStartedAtUtc = 0;

	// Total duration of the research job in seconds. 0 if not in research.
	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Research")
	int32 ResearchDurationSeconds = 0;

	// Content ID of the reward granted when research completes.
	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Research")
	FString ResearchOutputContentId;

	// Number of reward units granted on completion.
	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Research")
	int32 ResearchOutputQuantity = 0;

	// Kind of reward granted when research completes.
	UPROPERTY(BlueprintReadWrite, Category = "BeamFarm|Research")
	EBeamResearchOutputType ResearchOutputType = EBeamResearchOutputType::PlantModifier;

	// ─── Research utilities (C++ only; use UBeamFarmInventoryItemLibrary for Blueprint) ──────────

	// True when the local clock says the research timer has elapsed.
	// The server is authoritative — use this only for UI feedback, not to skip CollectResearch.
	bool IsResearchComplete() const
	{
		if (!bIsInResearch) return false;
		return FDateTime::UtcNow().ToUnixTimestamp() >= ResearchStartedAtUtc + ResearchDurationSeconds;
	}

	// Seconds until research finishes. Returns 0 if already complete or not in research.
	int64 GetResearchSecondsRemaining() const
	{
		if (!bIsInResearch) return 0LL;
		const int64 ReadyAt = ResearchStartedAtUtc + ResearchDurationSeconds;
		return FMath::Max<int64>(0LL, ReadyAt - FDateTime::UtcNow().ToUnixTimestamp());
	}

	// Progress fraction in [0, 1]. 0 if not in research, 1 when complete.
	float GetResearchProgress() const
	{
		if (!bIsInResearch || ResearchDurationSeconds <= 0) return 0.f;
		const float Elapsed = static_cast<float>(FDateTime::UtcNow().ToUnixTimestamp() - ResearchStartedAtUtc);
		return FMath::Clamp(Elapsed / static_cast<float>(ResearchDurationSeconds), 0.f, 1.f);
	}
};

/**
 * Blueprint-accessible utilities for FBeamFarmInventoryItem research state.
 * Mirror of the inline C++ helpers above; use these in Blueprints.
 */
UCLASS()
class BEAMPROJ_BEAMFARM_API UBeamFarmInventoryItemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// True when the local clock says the research timer has elapsed.
	// The server is authoritative — use this only for UI feedback, not to skip CollectResearch.
	UFUNCTION(BlueprintPure, Category = "BeamFarm|Research")
	static bool IsResearchComplete(const FBeamFarmInventoryItem& Item)
	{
		return Item.IsResearchComplete();
	}

	// Seconds until research finishes. Returns 0 if already complete or not in research.
	UFUNCTION(BlueprintPure, Category = "BeamFarm|Research")
	static int64 GetResearchSecondsRemaining(const FBeamFarmInventoryItem& Item)
	{
		return Item.GetResearchSecondsRemaining();
	}

	// Progress fraction in [0, 1]. 0 if not in research, 1 when complete.
	UFUNCTION(BlueprintPure, Category = "BeamFarm|Research")
	static float GetResearchProgress(const FBeamFarmInventoryItem& Item)
	{
		return Item.GetResearchProgress();
	}
};
