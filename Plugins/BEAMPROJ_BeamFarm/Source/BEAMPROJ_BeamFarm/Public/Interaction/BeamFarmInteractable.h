// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BeamFarmInteractable.generated.h"

/**
 * Implement this interface on any actor that the player can walk up to and interact with.
 *
 * ABeamFarmPlayerController drives the full flow:
 *   1. Player clicks/touches the actor.
 *   2. Controller moves the character toward GetInteractionPoint().
 *   3. When the character is within GetInteractionRadius(), Interact() is called automatically.
 *
 * All three functions are BlueprintNativeEvent — override them in C++ or Blueprint.
 * Default implementations: GetInteractionPoint → ZeroVector, GetInteractionRadius → 150, Interact → no-op.
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UBeamFarmInteractable : public UInterface
{
	GENERATED_BODY()
};

class BEAMPROJ_BEAMFARM_API IBeamFarmInteractable
{
	GENERATED_BODY()

public:
	// World location the character navigates to before interacting.
	UFUNCTION(BlueprintNativeEvent, Category = "BeamFarm|Interaction")
	FVector GetInteractionPoint() const;

	// Distance (cm) at which Interact() fires automatically.
	UFUNCTION(BlueprintNativeEvent, Category = "BeamFarm|Interaction")
	float GetInteractionRadius() const;

	// Perform the interaction. Called by ABeamFarmPlayerController when the character is close enough.
	UFUNCTION(BlueprintNativeEvent, Category = "BeamFarm|Interaction")
	void Interact(APawn* InstigatorPawn);
};
