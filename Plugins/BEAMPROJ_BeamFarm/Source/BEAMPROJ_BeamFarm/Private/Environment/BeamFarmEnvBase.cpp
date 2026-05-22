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

	EntryPoint = CreateDefaultSubobject<USceneComponent>(TEXT("EntryPoint"));
	EntryPoint->SetupAttachment(SceneRoot);
}

FVector ABeamFarmEnvBase::GetInteractionPoint_Implementation() const
{
	return EntryPoint->GetComponentLocation();
}

float ABeamFarmEnvBase::GetInteractionRadius_Implementation() const
{
	return Radius;
}

void ABeamFarmEnvBase::Interact_Implementation(APawn* InstigatorPawn)
{
	OnBuildingInteracted.Broadcast(this, InstigatorPawn);
	OnInteract(InstigatorPawn);
}
