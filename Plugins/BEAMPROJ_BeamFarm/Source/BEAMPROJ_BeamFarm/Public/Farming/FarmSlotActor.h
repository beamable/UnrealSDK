// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Farming/FarmTypes.h"
#include "Interaction/BeamFarmInteractable.h"
#include "BeamPlantData.h"
#include "BeamSeedData.h"
#include "FarmSlotActor.generated.h"

class UBoxComponent;
class UPaperSpriteComponent;
class UPaperSprite;
class UBeamPlantContent;

/**
 * A single plantable slot in a farm plot.
 *
 * Assign EmptySprite in the Blueprint Details panel.
 * GrowingSprite comes from the planted FBeamSeedData.
 * ReadyToHarvestSprite comes from the resolved FBeamPlantData (HarvestPlantData).
 * CropSpriteComp swaps between them automatically as the slot state changes.
 *
 * Override OnStateChanged in Blueprint for additional logic (sounds, particles).
 * Override OnHarvestFeedback for a pop/collect animation before the slot resets.
 *
 * Implements IBeamFarmInteractable — ABeamFarmPlayerController moves the character
 * within InteractionRadius before calling UBeamFarmSubsystem::HandleSlotInteraction().
 * Clicking the slot still fires OnSlotClicked() immediately for visual feedback.
 */
UCLASS(Blueprintable, BlueprintType)
class BEAMPROJ_BEAMFARM_API AFarmSlotActor : public AActor, public IBeamFarmInteractable
{
	GENERATED_BODY()

public:
	AFarmSlotActor();

	// Collision box for mouse/touch detection. Resize to match your sprite in BP.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamFarm|Slot|Components")
	TObjectPtr<UBoxComponent> InteractionBox;

	// Displays EmptySprite / GrowingSprite / ReadyToHarvestSprite depending on state.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamFarm|Slot|Components")
	TObjectPtr<UPaperSpriteComponent> CropSpriteComp;

	// Shown when no crop is planted. Leave null to hide the component when empty.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Slot|Sprites")
	TObjectPtr<UPaperSprite> EmptySprite;

	// Stable identifier for this slot.
	// Set a unique value per slot in the Level Editor (e.g. "slot_1", "slot_farm_a").
	// This is passed as PlantRequest.slotId and CollectRequest.slotId to the microservice.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Slot")
	FString SlotId;

	// How close (cm) the character must be before the farming interaction triggers.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Slot")
	float InteractionRadius = 150.f;

	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Slot")
	EFarmSlotState SlotState;

	// The seed that was planted — provides GrowingSprite and GrowTimeSeconds.
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Slot")
	FBeamSeedData PlantedSeed;

	// The resolved harvest plant data — provides ReadyToHarvestSprite.
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Slot")
	FBeamPlantData HarvestPlantData;

	// Fired whenever SlotState changes.
	UPROPERTY(BlueprintAssignable, Category = "BeamFarm|Slot")
	FOnFarmSlotStateChangedDelegate OnSlotStateChanged;

	// Plants a seed and starts the grow timer. No-op if slot is not Empty.
	// SeedData drives the grow time and growing visual; PlantData provides the ready-to-harvest visual.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Slot")
	void PlantCrop(const FBeamSeedData& SeedData, const FBeamPlantData& PlantData);

	// Resets the slot to Empty. Only valid when SlotState == ReadyToHarvest.
	// Does NOT add items to inventory — UBeamFarmSubsystem::OnItemsHarvested broadcasts that.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Slot")
	void Harvest();

	// Cancels an in-progress plant and reverts to Empty. Called when the server rejects PlantSeed.
	// Only valid when SlotState == Growing.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Slot")
	void CancelPlant();

	// Returns grow progress in [0, 1]. Returns 1 if ReadyToHarvest, 0 if Empty.
	UFUNCTION(BlueprintPure, Category = "BeamFarm|Slot")
	float GetGrowProgress() const;

	// Override in Blueprint for extra state-change logic (sounds, particles).
	// The sprite swap on CropSpriteComp already happens before this is called.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Slot")
	void OnStateChanged(EFarmSlotState NewState);

	// Override in Blueprint for collect animation/feedback.
	// Fires before the slot resets — PlantedSeed and HarvestPlantData are still valid here.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Slot")
	void OnHarvestFeedback();

	// Override in Blueprint for extra click logic (sound, highlight) without breaking routing.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Slot")
	void OnSlotClicked();

	// Called by UBeamFarmSubsystem when the grow duration has elapsed.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Slot")
	void MarkReadyToHarvest();

	// Restores a saved planting state without making a backend call.
	// RemainingGrowSeconds is the time left until harvest (0 = already ready).
	// Called by UBeamFarmSubsystem::RestoreSlotStates after login.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Slot")
	void RestorePlanting(const FBeamSeedData& SeedData, const FBeamPlantData& PlantData, float RemainingGrowSeconds);

	// IBeamFarmInteractable
	virtual FVector GetInteractionPoint_Implementation() const override;
	virtual float GetInteractionRadius_Implementation() const override;
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	float PlantedTimestamp = 0.f;

	void UpdateSprite(EFarmSlotState NewState);
	void SetSlotState(EFarmSlotState NewState);

	UFUNCTION()
	void HandleActorClicked(AActor* TouchedActor, FKey ButtonPressed);

	// Handlers for UBeamFarmSubsystem slot delegates — filtered by SlotId.
	UFUNCTION()
	void HandleSlotShouldPlant(const FString& InSlotId, const FBeamSeedData& SeedData, const FBeamPlantData& PlantData);

	UFUNCTION()
	void HandleSlotShouldHarvest(const FString& InSlotId);

	UFUNCTION()
	void HandleSlotShouldCancelPlant(const FString& InSlotId);
};
