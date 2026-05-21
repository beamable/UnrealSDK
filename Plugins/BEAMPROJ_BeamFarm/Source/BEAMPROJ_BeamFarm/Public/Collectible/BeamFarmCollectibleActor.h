// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/BeamFarmInteractable.h"
#include "BeamSeedData.h"
#include "BeamFarmCollectibleActor.generated.h"

class UCapsuleComponent;
class UPaperSpriteComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCollectiblePickedUp, ABeamFarmCollectibleActor*, Collectible, APawn*, Collector);

/**
 * A collectible item actor that the player can walk to and pick up.
 *
 * Spawned by UFarmCollectibleSpawner at designer-placed world locations.
 * When the player interacts with it, OnPickedUp fires, then the actor destroys itself.
 * The spawner listens to OnPickedUp and calls UFarmingComponent::OnItemsHarvested
 * (or equivalent) to add the material to the player's Beamable inventory.
 *
 * Override OnCollected in Blueprint for pick-up particle/sound effects.
 * Assign ItemData.Icon to CropSpriteComp in the Blueprint subclass.
 */
UCLASS(Blueprintable, BlueprintType)
class BEAMPROJ_BEAMFARM_API ABeamFarmCollectibleActor : public AActor, public IBeamFarmInteractable
{
	GENERATED_BODY()

public:
	ABeamFarmCollectibleActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamFarm|Collectible|Components")
	TObjectPtr<UCapsuleComponent> CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamFarm|Collectible|Components")
	TObjectPtr<UPaperSpriteComponent> SpriteComp;

	// The seed this collectible awards when picked up.
	// Set the ContentId to the plant.raw.material content ID of the seed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Collectible")
	FBeamSeedData ItemData;

	// How many units of ItemData the player receives on pick-up.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Collectible", meta = (ClampMin = "1"))
	int32 Quantity = 1;

	// Unique ID assigned by UFarmCollectibleSpawner at spawn time and sent to the microservice
	// via RegisterGroundItem. CollectGroundItem reads it back when the player picks up the item.
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Collectible")
	FString GroundItemId;

	// Distance (cm) the character must be within before the pick-up triggers.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Collectible")
	float InteractionRadius = 100.f;

	// Fired just before the actor is destroyed. Spawner listens here to update inventory.
	UPROPERTY(BlueprintAssignable, Category = "BeamFarm|Collectible")
	FOnCollectiblePickedUp OnPickedUp;

	// Override in Blueprint for collect VFX/SFX. Actor is destroyed after this returns.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Collectible")
	void OnCollected(APawn* Collector);

	// IBeamFarmInteractable
	virtual FVector GetInteractionPoint_Implementation() const override;
	virtual float GetInteractionRadius_Implementation() const override;
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
