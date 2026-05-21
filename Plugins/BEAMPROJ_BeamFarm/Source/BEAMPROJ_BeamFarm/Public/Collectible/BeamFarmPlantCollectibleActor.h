// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/BeamFarmInteractable.h"
#include "BeamPlantData.h"
#include "BeamFarmPlantCollectibleActor.generated.h"

class UCapsuleComponent;
class UPaperSpriteComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlantCollectiblePickedUp, ABeamFarmPlantCollectibleActor*, Collectible, APawn*, Collector);

/**
 * A world-placed plant item collectible the player can walk to and pick up.
 *
 * Spawned by UFarmPlantCollectibleSpawner or placed directly in the level.
 * When the player interacts with it, OnPickedUp fires, then the actor destroys itself.
 * The spawner listens to OnPickedUp and calls OnPlantCollectibleCollected so Blueprint
 * can add the plant item to the player's Beamable inventory.
 *
 * Override OnCollected in Blueprint for pick-up VFX/SFX.
 * Use SetPlantData() to assign item data — it updates SpriteComp automatically.
 */
UCLASS(Blueprintable, BlueprintType)
class BEAMPROJ_BEAMFARM_API ABeamFarmPlantCollectibleActor : public AActor, public IBeamFarmInteractable
{
	GENERATED_BODY()

public:
	ABeamFarmPlantCollectibleActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamFarm|Collectible|Components")
	TObjectPtr<UCapsuleComponent> CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamFarm|Collectible|Components")
	TObjectPtr<UPaperSpriteComponent> SpriteComp;

	// The plant item awarded when picked up. Set via SetPlantData() to also update the sprite.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Collectible")
	FBeamPlantData PlantData;

	// How many units of PlantData the player receives on pick-up.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Collectible", meta = (ClampMin = "1"))
	int32 Quantity = 1;

	// Unique ID assigned by UFarmPlantCollectibleSpawner at spawn time and sent to the microservice
	// via RegisterGroundItem. CollectGroundItem reads it back when the player picks up the item.
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Collectible")
	FString GroundItemId;

	// Distance (cm) the character must be within before the pick-up triggers.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Collectible")
	float InteractionRadius = 100.f;

	// Fired just before the actor is destroyed. Spawner listens here to update inventory.
	UPROPERTY(BlueprintAssignable, Category = "BeamFarm|Collectible")
	FOnPlantCollectiblePickedUp OnPickedUp;

	// Assigns PlantData and immediately applies ReadyToHarvestSprite to SpriteComp.
	// Always prefer this over setting PlantData directly.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Collectible")
	void SetPlantData(const FBeamPlantData& InPlantData);

	// Override in Blueprint for collect VFX/SFX. Actor is destroyed after this returns.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Collectible")
	void OnCollected(APawn* Collector);

	// IBeamFarmInteractable
	virtual FVector GetInteractionPoint_Implementation() const override;
	virtual float GetInteractionRadius_Implementation() const override;
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	virtual void BeginPlay() override;

private:
	void ApplySprite();
};
