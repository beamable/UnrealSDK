// Copyright Beamable, Inc. All Rights Reserved.

#include "Collectible/BeamFarmCollectibleActor.h"
#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"

ABeamFarmCollectibleActor::ABeamFarmCollectibleActor()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	CollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComp"));
	CollisionComp->SetupAttachment(SceneRoot);
	CollisionComp->SetCapsuleHalfHeight(32.f);
	CollisionComp->SetCapsuleRadius(24.f);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComp"));
	SpriteComp->SetupAttachment(SceneRoot);
	SpriteComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

FVector ABeamFarmCollectibleActor::GetInteractionPoint_Implementation() const
{
	return GetActorLocation();
}

float ABeamFarmCollectibleActor::GetInteractionRadius_Implementation() const
{
	return InteractionRadius;
}

void ABeamFarmCollectibleActor::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!InstigatorPawn)
	{
		return;
	}

	OnCollected(InstigatorPawn);
	OnPickedUp.Broadcast(this, InstigatorPawn);
	Destroy();
}
