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

void ABeamFarmCollectibleActor::BeginPlay()
{
	Super::BeginPlay();
	// Apply sprite for actors placed directly in the level with ItemInfo set in the Details panel.
	ApplySprite();
}

void ABeamFarmCollectibleActor::SetItemInfo(const FBeamFarmCollectibleInfo& Info)
{
	ItemInfo = Info;
	ApplySprite();
}

void ABeamFarmCollectibleActor::ApplySprite()
{
	UPaperSprite* Sprite = nullptr;

	if (ItemInfo.ItemType == TEXT("PlantItem"))
	{
		if (!ItemInfo.PlantData.ReadyToHarvestSprite.IsNull())
		{
			Sprite = ItemInfo.PlantData.ReadyToHarvestSprite.LoadSynchronous();
		}
	}
	else
	{
		// RawMaterial and any unrecognised type fall through to seed sprite.
		if (!ItemInfo.SeedData.SeedSprite.IsNull())
		{
			Sprite = ItemInfo.SeedData.SeedSprite.LoadSynchronous();
		}
	}

	SpriteComp->SetSprite(Sprite);
	SpriteComp->SetVisibility(Sprite != nullptr);
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
