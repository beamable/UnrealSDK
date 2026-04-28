// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FarmPlotActor.generated.h"

class AFarmSlotActor;

/**
 * A farm plot that owns N planting slots.
 *
 * Add transforms to SlotTransforms in the Blueprint Details panel to define
 * each slot's world position/rotation. Set SlotActorClass to your BP subclass
 * of AFarmSlotActor. Slots are spawned automatically at BeginPlay.
 *
 * The plot actor itself has no visual — it is a pure organizational container.
 */
UCLASS(Blueprintable, BlueprintType)
class BEAMPROJ_BEAMFARM_API AFarmPlotActor : public AActor
{
	GENERATED_BODY()

public:
	AFarmPlotActor();

	// World-space transforms for each slot. Set these in the Blueprint Details panel.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plot")
	TArray<FTransform> SlotTransforms;

	// Blueprint subclass of AFarmSlotActor to spawn for each slot.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plot")
	TSubclassOf<AFarmSlotActor> SlotActorClass;

	// Spawned slot actors. Populated at BeginPlay via InitializeSlots().
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Plot")
	TArray<TObjectPtr<AFarmSlotActor>> Slots;

	// Spawns slot actors at the configured SlotTransforms. Called automatically at BeginPlay.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Plot")
	void InitializeSlots();

	UFUNCTION(BlueprintPure, Category = "BeamFarm|Plot")
	TArray<AFarmSlotActor*> GetReadySlots() const;

	UFUNCTION(BlueprintPure, Category = "BeamFarm|Plot")
	TArray<AFarmSlotActor*> GetEmptySlots() const;

protected:
	virtual void BeginPlay() override;
};
