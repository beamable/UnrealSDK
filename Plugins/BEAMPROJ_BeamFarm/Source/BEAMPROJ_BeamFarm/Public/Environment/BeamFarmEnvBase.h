// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeamFarmEnvBase.generated.h"

class UCapsuleComponent;
class UPaperSpriteComponent;

/**
 * Base actor for all collidable and interactable environment objects in BeamFarm.
 * Provides a UCapsuleComponent for collision and a UPaperSpriteComponent for the
 * 2D visual — both as siblings under a neutral scene root, ready to subclass in Blueprint.
 */
UCLASS(Blueprintable, BlueprintType)
class BEAMPROJ_BEAMFARM_API ABeamFarmEnvBase : public AActor
{
	GENERATED_BODY()

public:
	ABeamFarmEnvBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamFarm|Components")
	TObjectPtr<UCapsuleComponent> CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BeamFarm|Components")
	TObjectPtr<UPaperSpriteComponent> SpriteComp;
};
