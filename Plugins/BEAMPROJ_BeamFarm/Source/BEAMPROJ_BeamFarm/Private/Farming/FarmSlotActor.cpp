// Copyright Beamable, Inc. All Rights Reserved.

#include "Farming/FarmSlotActor.h"
#include "Subsystem/BeamFarmSubsystem.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
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
	UpdateSprite(EFarmSlotState::Empty);

	UBeamFarmSubsystem* Sub = GetWorld()->GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (Sub)
	{
		Sub->OnSlotShouldPlant.AddDynamic(this, &AFarmSlotActor::HandleSlotShouldPlant);
		Sub->OnSlotShouldHarvest.AddDynamic(this, &AFarmSlotActor::HandleSlotShouldHarvest);
		Sub->OnSlotShouldCancelPlant.AddDynamic(this, &AFarmSlotActor::HandleSlotShouldCancelPlant);
		Sub->RegisterSlotActor(SlotId, this);
	}
}

void AFarmSlotActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UBeamFarmSubsystem* Sub = GetWorld()->GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (Sub)
	{
		Sub->OnSlotShouldPlant.RemoveDynamic(this, &AFarmSlotActor::HandleSlotShouldPlant);
		Sub->OnSlotShouldHarvest.RemoveDynamic(this, &AFarmSlotActor::HandleSlotShouldHarvest);
		Sub->OnSlotShouldCancelPlant.RemoveDynamic(this, &AFarmSlotActor::HandleSlotShouldCancelPlant);
		Sub->UnregisterSlotActor(SlotId);

		if (SlotState == EFarmSlotState::Growing)
		{
			Sub->NotifySlotCleared(SlotId);
		}
	}

	Super::EndPlay(EndPlayReason);
}

void AFarmSlotActor::PlantCrop(const FBeamSeedData& SeedData, const FBeamPlantData& PlantData)
{
	if (SlotState != EFarmSlotState::Empty)
	{
		return;
	}

	PlantedSeed = SeedData;
	HarvestPlantData = PlantData;
	PlantedTimestamp = GetWorld()->GetTimeSeconds();

	SetSlotState(EFarmSlotState::Growing);

	UBeamFarmSubsystem* Sub = GetWorld()->GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (Sub)
	{
		Sub->NotifySlotPlanted(SlotId, this, SeedData.GrowTimeSeconds);
	}
}

void AFarmSlotActor::Harvest()
{
	if (SlotState != EFarmSlotState::ReadyToHarvest)
	{
		return;
	}

	OnHarvestFeedback();

	PlantedSeed = FBeamSeedData();
	HarvestPlantData = FBeamPlantData();
	PlantedTimestamp = 0.f;

	SetSlotState(EFarmSlotState::Empty);
}

void AFarmSlotActor::CancelPlant()
{
	if (SlotState != EFarmSlotState::Growing)
	{
		return;
	}

	PlantedSeed = FBeamSeedData();
	HarvestPlantData = FBeamPlantData();
	PlantedTimestamp = 0.f;

	SetSlotState(EFarmSlotState::Empty);

	UBeamFarmSubsystem* Sub = GetWorld()->GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (Sub)
	{
		Sub->NotifySlotCleared(SlotId);
	}
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
	return FMath::Clamp(Elapsed / FMath::Max(PlantedSeed.GrowTimeSeconds, 1.f), 0.f, 1.f);
}

void AFarmSlotActor::UpdateSprite(EFarmSlotState NewState)
{
	UPaperSprite* TargetSprite = nullptr;

	switch (NewState)
	{
	case EFarmSlotState::Empty:
		TargetSprite = EmptySprite;
		break;
	case EFarmSlotState::Growing:
		TargetSprite = !PlantedSeed.GrowingSprite.IsNull() ? PlantedSeed.GrowingSprite.LoadSynchronous() : nullptr;
		break;
	case EFarmSlotState::ReadyToHarvest:
		TargetSprite = !HarvestPlantData.ReadyToHarvestSprite.IsNull() ? HarvestPlantData.ReadyToHarvestSprite.LoadSynchronous() : nullptr;
		break;
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

void AFarmSlotActor::MarkReadyToHarvest()
{
	if (SlotState != EFarmSlotState::Growing)
	{
		return;
	}
	SetSlotState(EFarmSlotState::ReadyToHarvest);
}

void AFarmSlotActor::RestorePlanting(const FBeamSeedData& SeedData, const FBeamPlantData& PlantData, float RemainingGrowSeconds)
{
	if (SlotState != EFarmSlotState::Empty)
	{
		return;
	}

	PlantedSeed = SeedData;
	HarvestPlantData = PlantData;

	// Backdate PlantedTimestamp so GetGrowProgress() reflects the already-elapsed time correctly.
	const float AlreadyElapsed = FMath::Max(0.f, SeedData.GrowTimeSeconds - RemainingGrowSeconds);
	PlantedTimestamp = GetWorld()->GetTimeSeconds() - AlreadyElapsed;

	if (RemainingGrowSeconds <= 0.f)
	{
		SetSlotState(EFarmSlotState::ReadyToHarvest);
	}
	else
	{
		SetSlotState(EFarmSlotState::Growing);

		UBeamFarmSubsystem* Sub = GetWorld()->GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
		if (Sub)
		{
			Sub->NotifySlotPlanted(SlotId, this, RemainingGrowSeconds);
		}
	}
}

void AFarmSlotActor::HandleActorClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	// Visual/audio feedback only — the interaction itself is deferred until the character
	// walks within InteractionRadius (handled by ABeamFarmPlayerController).
	OnSlotClicked();
}

FVector AFarmSlotActor::GetInteractionPoint_Implementation() const
{
	return GetActorLocation();
}

float AFarmSlotActor::GetInteractionRadius_Implementation() const
{
	return InteractionRadius;
}

void AFarmSlotActor::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!InstigatorPawn)
	{
		return;
	}

	UBeamFarmSubsystem* Sub = GetWorld()->GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (!Sub)
	{
		return;
	}

	FBeamFarmInteractionRequest Request;
	Request.SlotId = SlotId;
	Request.SlotState = SlotState;
	Request.PlantedSeed = PlantedSeed;
	Sub->HandleSlotInteraction(Request);
}

void AFarmSlotActor::HandleSlotShouldPlant(const FString& InSlotId, const FBeamSeedData& SeedData, const FBeamPlantData& PlantData)
{
	if (InSlotId == SlotId)
	{
		PlantCrop(SeedData, PlantData);
	}
}

void AFarmSlotActor::HandleSlotShouldHarvest(const FString& InSlotId)
{
	if (InSlotId == SlotId)
	{
		Harvest();
	}
}

void AFarmSlotActor::HandleSlotShouldCancelPlant(const FString& InSlotId)
{
	if (InSlotId == SlotId)
	{
		CancelPlant();
	}
}
