// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/BeamFarmInteractable.h"
#include "BeamFarmPlayerController.generated.h"

class ABeamFarmCharacter;

/**
 * Player controller for the BeamFarm demo.
 *
 * Handles click-to-move and the generic interaction flow:
 *   - Click/touch on an IBeamFarmInteractable → character walks to it → Interact() fires on arrival.
 *   - Click/touch on empty space → character walks to the hit location.
 *
 * Set this (or a Blueprint subclass) as the PlayerControllerClass in your GameMode.
 * Enable bShowMouseCursor on a Blueprint subclass if you need a visible cursor.
 *
 * Override the BlueprintImplementableEvent functions for feedback:
 *   - OnInteractionPending    — player clicked an interactable, character is on its way.
 *   - OnInteractionExecuted   — character reached the interactable and Interact() was called.
 *   - OnMoveToLocation        — player clicked empty space, character is walking there.
 */
UCLASS(Blueprintable, BlueprintType)
class BEAMPROJ_BEAMFARM_API ABeamFarmPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABeamFarmPlayerController();

	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;

	// Radius used when the interactable's GetInteractionRadius() returns the default value.
	// Override per-interactable to tune per-object.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Interaction")
	float DefaultInteractionRadius = 150.f;

	// Override in Blueprint: the character is now moving toward TargetActor.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Interaction")
	void OnInteractionPending(AActor* TargetActor);

	// Override in Blueprint: Interact() was called on TargetActor.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Interaction")
	void OnInteractionExecuted(AActor* TargetActor);

	// Override in Blueprint: the character is moving to an empty location (no interactable).
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Interaction")
	void OnMoveToLocation(const FVector& WorldLocation);

private:
	TScriptInterface<IBeamFarmInteractable> PendingInteractable;

	UFUNCTION()
	void HandleClick();

	UFUNCTION()
	void HandleTouch(ETouchIndex::Type FingerIndex, FVector TouchLocation);

	void ProcessHitResult(const FHitResult& HitResult);
	void RequestInteractionWith(TScriptInterface<IBeamFarmInteractable> Interactable);
	void CheckProximityAndInteract();
	void ClearPendingInteraction();

	ABeamFarmCharacter* GetBeamFarmCharacter() const;
};
