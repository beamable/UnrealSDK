// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AITypes.h"
#include "GameFramework/Character.h"
#include "AI/Navigation/NavigationTypes.h"
#include "Navigation/PathFollowingComponent.h"

#include "BeamFarmCharacter.generated.h"

class UPathFollowingComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeamFarmMovementComplete);

/**
 * Character class for the BeamFarm demo.
 *
 * Supports click-to-move driven by ABeamFarmPlayerController.
 * Uses PathFollowingComponent directly for navigation without requiring an AIController.
 * Broadcasts OnMovementComplete when the destination is reached.
 *
 * Assign this class (or a Blueprint subclass) as the default pawn in your GameMode.
 * Attach UFarmingComponent to interact with farm slots.
 */
UCLASS(Blueprintable, BlueprintType)
class BEAMPROJ_BEAMFARM_API ABeamFarmCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABeamFarmCharacter();

protected:
	// Path following component for navigation
	UPROPERTY()
	UPathFollowingComponent* PathFollowingComp;

public:
	// How close (cm) to the destination before the character is considered arrived.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Character")
	float ArrivalThreshold = 50.f;

	// Fires when the character arrives within ArrivalThreshold of the destination.
	// Not fired when movement is cancelled by StopMovementToTarget().
	UPROPERTY(BlueprintAssignable, Category = "BeamFarm|Character")
	FOnBeamFarmMovementComplete OnMovementComplete;

	virtual void BeginPlay() override;

	// Begin moving toward Destination. Overwrites any current movement target.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Character")
	void MoveToWorldLocation(const FVector& Destination);

	// Cancel the current move-to-target and halt immediately.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Character")
	void StopMovementToTarget();

	UFUNCTION(BlueprintPure, Category = "BeamFarm|Character")
	bool IsMovingToTarget() const { return bMovingToTarget; }

	// Callback for when the character reaches the destination
	void OnMoveCompleted(FAIRequestID FaiRequestID, const FPathFollowingResult& PathFollowingResult);
	
	
private:
	bool bMovingToTarget = false;
	FAIRequestID CurrentMoveRequestID;
};
