// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/BeamFarmInteractable.h"
#include "Farming/FarmTypes.h"
#include "BeamFarmCollectibleActor.generated.h"

class UCapsuleComponent;
class UPaperSpriteComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCollectiblePickedUp, ABeamFarmCollectibleActor*, Collectible, APawn*, Collector);

/**
 * A collectible item actor that the player can walk to and pick up.
 *
 * Spawned by UFarmCollectibleSpawner at designer-placed world locations.
 * When the player interacts with it, OnPickedUp fires, then the actor destroys itself.
 * The spawner listens to OnPickedUp and calls CollectGroundItem via UBeamFarmSubsystem.
 *
 * Override OnCollected in Blueprint for pick-up particle/sound effects.
 * Call SetItemInfo() after spawning — it stores item data and applies the correct sprite.
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

	// Unified item info set by the spawner at spawn time.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Collectible")
	FBeamFarmCollectibleInfo ItemInfo;

	// Unique ID assigned by the spawner at spawn time and sent to the microservice
	// via RegisterGroundItem. CollectGroundItem reads it back when the player picks up the item.
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Collectible")
	FString GroundItemId;

	// Set by UBeamFarmSubsystem at spawn time so HandleCollectiblePickedUp can route
	// the pick-up event back to the correct spawner's delegate.
	UPROPERTY(BlueprintReadOnly, Category = "BeamFarm|Collectible")
	FString SpawnerId;

	// Distance (cm) the character must be within before the pick-up triggers.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Collectible")
	float InteractionRadius = 100.f;

	// Fired just before the actor is destroyed. Spawner listens here to update inventory.
	UPROPERTY(BlueprintAssignable, Category = "BeamFarm|Collectible")
	FOnCollectiblePickedUp OnPickedUp;

	// Stores ItemInfo and applies the appropriate sprite based on ItemInfo.ItemType.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Collectible")
	void SetItemInfo(const FBeamFarmCollectibleInfo& Info);

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
