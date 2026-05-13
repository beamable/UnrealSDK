// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/BeamFarmInteractable.h"
#include "Farming/FarmTypes.h"
#include "BeamFarmEnvBase.generated.h"

class UCapsuleComponent;
class UPaperSpriteComponent;
class ABeamFarmEnvBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBuildingInteractedDelegate, ABeamFarmEnvBase*, Building, APawn*, InstigatorPawn);

/**
 * Base actor for all collidable and interactable environment objects in BeamFarm.
 * Provides a UCapsuleComponent for collision and a UPaperSpriteComponent for the
 * 2D visual — both as siblings under a neutral scene root, ready to subclass in Blueprint.
 *
 * Implements IBeamFarmInteractable so clicks on buildings redirect movement to EntryPoint
 * instead of the blocked navmesh location under the building's collision.
 * Position EntryPoint in front of the door in each Blueprint subclass.
 */
UCLASS(Blueprintable, BlueprintType)
class BEAMPROJ_BEAMFARM_API ABeamFarmEnvBase : public AActor, public IBeamFarmInteractable
{
	GENERATED_BODY()

public:
	ABeamFarmEnvBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamFarm|Components")
	TObjectPtr<UCapsuleComponent> CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamFarm|Components")
	TObjectPtr<UPaperSpriteComponent> SpriteComp;

	// Move this in front of the building door in each Blueprint subclass.
	// The character will navigate here instead of the blocked building surface.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamFarm|Components")
	TObjectPtr<USceneComponent> EntryPoint;

	// The radius for interactions with this building. PlayerController uses this to determine when the character has reached the building.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Components")
	float Radius = 100;

	// Set this per-building Blueprint to identify which UI panel to open on interact.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Building")
	EBeamFarmBuildingType BuildingType = EBeamFarmBuildingType::None;

	// Fired when the player interacts with this building. PlayerController listens to open the HUD.
	UPROPERTY(BlueprintAssignable, Category = "BeamFarm|Building")
	FOnBuildingInteractedDelegate OnBuildingInteracted;

	// Override in Blueprint for per-building effects (door open animation, sound, etc.).
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Building")
	void OnInteract(APawn* InstigatorPawn);

	// IBeamFarmInteractable
	virtual FVector GetInteractionPoint_Implementation() const override;
	virtual float GetInteractionRadius_Implementation() const override;
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
