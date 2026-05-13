// Copyright Beamable, Inc. All Rights Reserved.

#include "Collectible/BeamFarmCollectibleSpawner.h"
#include "Collectible/BeamFarmCollectibleActor.h"
#include "Engine/World.h"
#include "TimerManager.h"

UFarmCollectibleSpawner::UFarmCollectibleSpawner()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFarmCollectibleSpawner::BeginPlay()
{
	Super::BeginPlay();
	StartSpawning();
}

void UFarmCollectibleSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	StopSpawning();
	Super::EndPlay(EndPlayReason);
}

void UFarmCollectibleSpawner::StartSpawning()
{
	if (SpawnTransforms.IsEmpty() || !CollectibleClass)
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&UFarmCollectibleSpawner::OnSpawnTimer,
		SpawnIntervalSeconds,
		true,
		0.f  // fire immediately on start
	);
}

void UFarmCollectibleSpawner::StopSpawning()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	}
}

void UFarmCollectibleSpawner::SpawnCollectibleNow()
{
	if (!CollectibleClass || SpawnTransforms.IsEmpty())
	{
		return;
	}

	// Find a spawn slot that isn't occupied by a live collectible.
	const int32 SlotCount = SpawnTransforms.Num();
	for (int32 Attempt = 0; Attempt < SlotCount; ++Attempt)
	{
		const int32 Index = (NextSpawnIndex + Attempt) % SlotCount;
		const FTransform& SpawnT = SpawnTransforms[Index];

		// Check if any active collectible is already at this slot (within 10 cm).
		bool bSlotOccupied = false;
		for (const ABeamFarmCollectibleActor* Existing : ActiveCollectibles)
		{
			if (IsValid(Existing) && FVector::Dist2D(Existing->GetActorLocation(), SpawnT.GetLocation()) < 10.f)
			{
				bSlotOccupied = true;
				break;
			}
		}

		if (bSlotOccupied)
		{
			continue;
		}

		FActorSpawnParameters Params;
		Params.Owner = GetOwner();
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		ABeamFarmCollectibleActor* Spawned = GetWorld()->SpawnActor<ABeamFarmCollectibleActor>(CollectibleClass, SpawnT, Params);
		if (Spawned)
		{
			Spawned->ItemData = MaterialData;
			Spawned->Quantity = QuantityPerCollectible;
			Spawned->OnPickedUp.AddDynamic(this, &UFarmCollectibleSpawner::HandlePickedUp);
			ActiveCollectibles.Add(Spawned);
			NextSpawnIndex = (Index + 1) % SlotCount;
			OnCollectibleSpawned(Spawned, SpawnT);
		}
		return;
	}
}

void UFarmCollectibleSpawner::OnSpawnTimer()
{
	// Remove any stale (destroyed) entries first.
	ActiveCollectibles.RemoveAll([](const TObjectPtr<ABeamFarmCollectibleActor>& C) { return !IsValid(C); });

	if (ActiveCollectibles.Num() >= MaxActiveCollectibles)
	{
		return;
	}

	SpawnCollectibleNow();
}

void UFarmCollectibleSpawner::HandlePickedUp(ABeamFarmCollectibleActor* Collectible, APawn* Collector)
{
	ActiveCollectibles.Remove(Collectible);
	OnCollectibleCollected(Collectible, Collector, MaterialData, QuantityPerCollectible);
}
