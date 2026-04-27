// Copyright Beamable, Inc. All Rights Reserved.

#include "Environment/BeamFarmEnvBase.h"
#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"

ABeamFarmEnvBase::ABeamFarmEnvBase()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CapsuleComp->SetupAttachment(SceneRoot);

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComp"));
	SpriteComp->SetupAttachment(SceneRoot);
}
