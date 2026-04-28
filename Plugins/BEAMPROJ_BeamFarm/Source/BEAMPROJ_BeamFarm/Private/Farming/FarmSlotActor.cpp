// Copyright Beamable, Inc. All Rights Reserved.

#include "Farming/FarmSlotActor.h"
#include "Farming/FarmingComponent.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "Engine/World.h"

AFarmSlotActor::AFarmSlotActor()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	CropSpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CropSpriteComp"));
	CropSpriteComp->SetupAttachment(Root);
	CropSpriteComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(Root);
	InteractionBox->SetBoxExtent(FVector(64.f, 64.f, 8.f));
	InteractionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	SlotState = EFarmSlotState::Empty;
}

void AFarmSlotActor::BeginPlay()
{
	Super::BeginPlay();

	OnClicked.AddDynamic(this, &AFarmSlotActor::HandleActorClicked);

	// Apply the empty sprite (or hide) on spawn
	UpdateSprite(EFarmSlotState::Empty);
}

void AFarmSlotActor::PlantCrop(const FFarmCropData& CropData)
{
	if (SlotState != EFarmSlotState::Empty)
	{
		return;
	}

	PlantedCrop = CropData;
	PlantedTimestamp = GetWorld()->GetTimeSeconds();

	SetSlotState(EFarmSlotState::Growing);

	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(this, &AFarmSlotActor::OnGrowTimerComplete);
	GetWorldTimerManager().SetTimer(GrowTimerHandle, TimerDelegate, CropData.GrowTimeSeconds, false);
}

void AFarmSlotActor::Harvest()
{
	if (SlotState != EFarmSlotState::ReadyToHarvest)
	{
		return;
	}

	OnHarvestFeedback();

	PlantedCrop = FFarmCropData{};
	PlantedTimestamp = 0.f;

	SetSlotState(EFarmSlotState::Empty);
}

float AFarmSlotActor::GetGrowProgress() const
{
	if (SlotState == EFarmSlotState::Empty)
	{
		return 0.f;
	}
	if (SlotState == EFarmSlotState::ReadyToHarvest)
	{
		return 1.f;
	}

	const float Elapsed = GetWorld()->GetTimeSeconds() - PlantedTimestamp;
	return FMath::Clamp(Elapsed / FMath::Max(PlantedCrop.GrowTimeSeconds, 1.f), 0.f, 1.f);
}

void AFarmSlotActor::UpdateSprite(EFarmSlotState NewState)
{
	UPaperSprite* TargetSprite = nullptr;

	switch (NewState)
	{
		case EFarmSlotState::Empty:          TargetSprite = EmptySprite;                        break;
		case EFarmSlotState::Growing:        TargetSprite = PlantedCrop.GrowingSprite;          break;
		case EFarmSlotState::ReadyToHarvest: TargetSprite = PlantedCrop.ReadyToHarvestSprite;   break;
	}

	CropSpriteComp->SetSprite(TargetSprite);
	CropSpriteComp->SetVisibility(TargetSprite != nullptr);
}

void AFarmSlotActor::SetSlotState(EFarmSlotState NewState)
{
	SlotState = NewState;
	UpdateSprite(NewState);
	OnStateChanged(NewState);
	OnSlotStateChanged.Broadcast(this, NewState);
}

void AFarmSlotActor::OnGrowTimerComplete()
{
	SetSlotState(EFarmSlotState::ReadyToHarvest);
}

void AFarmSlotActor::HandleActorClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	OnSlotClicked();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC)
	{
		return;
	}

	UFarmingComponent* FarmComp = PC->GetPawn()->FindComponentByClass<UFarmingComponent>();
	if (FarmComp)
	{
		FarmComp->InteractWithSlot(this);
	}
}
