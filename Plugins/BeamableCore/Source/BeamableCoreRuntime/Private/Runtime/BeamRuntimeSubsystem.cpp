// Fill out your copyright notice in the Description page of Project Settings.


#include "Runtime/BeamRuntimeSubsystem.h"

void UBeamRuntimeSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Runtime = Cast<UBeamRuntime>(Collection.InitializeDependency(UBeamRuntime::StaticClass()));

	Runtime->OnInitialized.AddDynamic(this, &UBeamRuntimeSubsystem::OnBeamableReady);
	Runtime->OnRuntimeUserSlotAuthenticatedEvents.AddDynamic(this, &UBeamRuntimeSubsystem::OnUserSlotAuthenticated);
	Runtime->OnRuntimeUserSlotClearedEvent.AddDynamic(this, &UBeamRuntimeSubsystem::OnUserSlotCleared);

	for (const auto& SlotName : Runtime->CoreSettings->RuntimeUserSlots)
		UserSlotInitialDataLoaded.Add(SlotName, false);
}

void UBeamRuntimeSubsystem::Deinitialize()
{
	Super::Deinitialize();

	Runtime->OnInitialized.RemoveDynamic(this, &UBeamRuntimeSubsystem::OnBeamableReady);
	Runtime->OnRuntimeUserSlotAuthenticatedEvents.RemoveDynamic(this, &UBeamRuntimeSubsystem::OnUserSlotAuthenticated);
	Runtime->OnRuntimeUserSlotClearedEvent.RemoveDynamic(this, &UBeamRuntimeSubsystem::OnUserSlotCleared);
}

bool UBeamRuntimeSubsystem::IsInitialized(FUserSlot Slot) const
{
	return UserSlotInitialDataLoaded.Contains(Slot) ? UserSlotInitialDataLoaded.FindChecked(Slot) : false;
}

bool UBeamRuntimeSubsystem::AreAllInitialized() const
{
	bool bAreAllInitialized = true;
	for (const auto& SlotInitialDataLoaded : UserSlotInitialDataLoaded)
	{
		bAreAllInitialized &= SlotInitialDataLoaded.Value;
	}
	return bAreAllInitialized;
}

void UBeamRuntimeSubsystem::TriggerOnInitialUserSlotDataReady(FUserSlot Slot)
{
	UserSlotInitialDataLoaded[Slot] = true;
	OnInitialUserSlotDataReady.Broadcast(Slot);

	if (AreAllInitialized())
		OnAllInitialUserSlotDataReady.Broadcast();
}


void UBeamRuntimeSubsystem::OnBeamableReady_Implementation()
{
}

void UBeamRuntimeSubsystem::OnUserSlotAuthenticated_Implementation(FUserSlot UserSlot)
{
}

void UBeamRuntimeSubsystem::OnUserSlotCleared_Implementation(FUserSlot UserSlot, EUserSlotClearedReason ClearedReason)
{
}
