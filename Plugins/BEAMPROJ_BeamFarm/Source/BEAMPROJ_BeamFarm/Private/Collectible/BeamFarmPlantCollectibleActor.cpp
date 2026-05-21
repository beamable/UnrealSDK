// Copyright Beamable, Inc. All Rights Reserved.

#include "Collectible/BeamFarmPlantCollectibleActor.h"
#include "Components/CapsuleComponent.h"
#include "PaperSpriteComponent.h"

ABeamFarmPlantCollectibleActor::ABeamFarmPlantCollectibleActor()
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

void ABeamFarmPlantCollectibleActor::BeginPlay()
{
	Super::BeginPlay();
	// Apply sprite for actors placed directly in the level with PlantData set in the Details panel.
	ApplySprite();
}

void ABeamFarmPlantCollectibleActor::SetPlantData(const FBeamPlantData& InPlantData)
{
	PlantData = InPlantData;
	ApplySprite();
}

void ABeamFarmPlantCollectibleActor::ApplySprite()
{
	if (PlantData.ReadyToHarvestSprite.IsNull())
	{
		SpriteComp->SetVisibility(false);
		return;
	}

	UPaperSprite* Sprite = PlantData.ReadyToHarvestSprite.LoadSynchronous();
	SpriteComp->SetSprite(Sprite);
	SpriteComp->SetVisibility(Sprite != nullptr);
}

FVector ABeamFarmPlantCollectibleActor::GetInteractionPoint_Implementation() const
{
	return GetActorLocation();
}

float ABeamFarmPlantCollectibleActor::GetInteractionRadius_Implementation() const
{
	return InteractionRadius;
}

void ABeamFarmPlantCollectibleActor::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!InstigatorPawn)
	{
		return;
	}

	OnCollected(InstigatorPawn);
	OnPickedUp.Broadcast(this, InstigatorPawn);
	Destroy();
}
