// Copyright Beamable, Inc. All Rights Reserved.

#include "Farming/FarmPlotActor.h"
#include "Farming/FarmSlotActor.h"
#include "Engine/World.h"

AFarmPlotActor::AFarmPlotActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("Root")));
}

void AFarmPlotActor::BeginPlay()
{
	Super::BeginPlay();
	InitializeSlots();
}

void AFarmPlotActor::InitializeSlots()
{
	if (!SlotActorClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("AFarmPlotActor: SlotActorClass is not set on %s"), *GetName());
		return;
	}

	for (AFarmSlotActor* ExistingSlot : Slots)
	{
		if (ExistingSlot)
		{
			ExistingSlot->Destroy();
		}
	}
	Slots.Empty();

	UWorld* World = GetWorld();
	for (const FTransform& SlotTransform : SlotTransforms)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AFarmSlotActor* NewSlot = World->SpawnActor<AFarmSlotActor>(SlotActorClass, SlotTransform, SpawnParams);
		if (NewSlot)
		{
			Slots.Add(NewSlot);
		}
	}
}

TArray<AFarmSlotActor*> AFarmPlotActor::GetReadySlots() const
{
	TArray<AFarmSlotActor*> Result;
	for (AFarmSlotActor* Slot : Slots)
	{
		if (Slot && Slot->SlotState == EFarmSlotState::ReadyToHarvest)
		{
			Result.Add(Slot);
		}
	}
	return Result;
}

TArray<AFarmSlotActor*> AFarmPlotActor::GetEmptySlots() const
{
	TArray<AFarmSlotActor*> Result;
	for (AFarmSlotActor* Slot : Slots)
	{
		if (Slot && Slot->SlotState == EFarmSlotState::Empty)
		{
			Result.Add(Slot);
		}
	}
	return Result;
}
