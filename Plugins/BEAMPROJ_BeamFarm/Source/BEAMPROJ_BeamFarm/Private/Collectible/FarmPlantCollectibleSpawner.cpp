// Copyright Beamable, Inc. All Rights Reserved.

#include "Collectible/FarmPlantCollectibleSpawner.h"
#include "Collectible/BeamFarmPlantCollectibleActor.h"
#include "Contents/BeamPlantContent.h"
#include "Subsystems/Content/BeamContentSubsystem.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#if WITH_EDITOR
#include "Components/LineBatchComponent.h"
#endif

// Draws a wireframe box into a ULineBatchComponent (12 edges, persistent lifetime).
#if WITH_EDITOR
static void BatchDrawBox(ULineBatchComponent* Batch, FVector Center, FVector HalfExtent, FLinearColor Color, float Thickness = 2.f)
{
	const float X = HalfExtent.X, Y = HalfExtent.Y, Z = HalfExtent.Z;
	const FVector C[8] = {
		Center + FVector(-X, -Y, -Z), Center + FVector( X, -Y, -Z),
		Center + FVector( X,  Y, -Z), Center + FVector(-X,  Y, -Z),
		Center + FVector(-X, -Y,  Z), Center + FVector( X, -Y,  Z),
		Center + FVector( X,  Y,  Z), Center + FVector(-X,  Y,  Z),
	};
	constexpr int32 Edges[12][2] = {
		{0,1},{1,2},{2,3},{3,0},   // bottom face
		{4,5},{5,6},{6,7},{7,4},   // top face
		{0,4},{1,5},{2,6},{3,7},   // verticals
	};
	for (const auto& E : Edges)
	{
		Batch->DrawLine(C[E[0]], C[E[1]], Color, /*Depth*/0, Thickness, /*LifeTime*/-1.f);
	}
}
#endif

UFarmPlantCollectibleSpawner::UFarmPlantCollectibleSpawner()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFarmPlantCollectibleSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (bDrawDebugZonesOnBeginPlay)
	{
		DrawDebugZones();
	}

	StartSpawning();
}

void UFarmPlantCollectibleSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	StopSpawning();
	Super::EndPlay(EndPlayReason);
}

void UFarmPlantCollectibleSpawner::OnRegister()
{
	Super::OnRegister();

#if WITH_EDITOR
	UWorld* World = GetWorld();
	if (World && World->WorldType == EWorldType::Editor)
	{
		RebuildEditorVisualization();
	}
#endif
}

void UFarmPlantCollectibleSpawner::OnUnregister()
{
#if WITH_EDITOR
	if (IsValid(EditorLineBatch))
	{
		EditorLineBatch->DestroyComponent();
		EditorLineBatch = nullptr;
	}
#endif
	Super::OnUnregister();
}

#if WITH_EDITOR
void UFarmPlantCollectibleSpawner::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UWorld* World = GetWorld();
	if (World && World->WorldType == EWorldType::Editor)
	{
		RebuildEditorVisualization();
	}
}

void UFarmPlantCollectibleSpawner::RebuildEditorVisualization()
{
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

	// Create or flush the dedicated line batch for zone outlines.
	if (!IsValid(EditorLineBatch))
	{
		EditorLineBatch = NewObject<ULineBatchComponent>(Owner, NAME_None, RF_Transient);
		EditorLineBatch->SetupAttachment(Owner->GetRootComponent());
		EditorLineBatch->SetHiddenInGame(true);
		EditorLineBatch->bIsEditorOnly = true;
		EditorLineBatch->RegisterComponentWithWorld(GetWorld());
	}
	else
	{
		EditorLineBatch->Flush();
	}

	const float DrawZ  = SpawnZ + 10.f;   // small offset so lines sit above the ground plane
	const float BoxH   = 8.f;             // flat box half-height (Z extent)

	// Base area — blue, only when SpawnZones is empty (it's the active fallback).
	if (SpawnZones.IsEmpty())
	{
		BatchDrawBox(EditorLineBatch,
			FVector(BaseAreaCenter.X, BaseAreaCenter.Y, DrawZ),
			FVector(BaseAreaHalfExtents.X, BaseAreaHalfExtents.Y, BoxH),
			FLinearColor(0.2f, 0.4f, 1.f));
	}

	// Spawn zones — green, brightness proportional to weight.
	for (const FBeamFarmSpawnZone& Zone : SpawnZones)
	{
		const float T = FMath::Clamp(Zone.Weight / 5.f, 0.f, 1.f);
		const FLinearColor Green(0.f, 0.35f + 0.65f * T, 0.f);
		BatchDrawBox(EditorLineBatch,
			FVector(Zone.Center.X, Zone.Center.Y, DrawZ),
			FVector(Zone.HalfExtents.X, Zone.HalfExtents.Y, BoxH),
			Green);
	}

	// Exclusion zones — red.
	for (const FBeamFarmExclusionZone& Zone : ExclusionZones)
	{
		BatchDrawBox(EditorLineBatch,
			FVector(Zone.Center.X, Zone.Center.Y, DrawZ),
			FVector(Zone.HalfExtents.X, Zone.HalfExtents.Y, BoxH),
			FLinearColor::Red);
	}
}
#endif

void UFarmPlantCollectibleSpawner::StartSpawning()
{
	if (!CollectibleClass || PlantContentIds.IsEmpty())
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&UFarmPlantCollectibleSpawner::OnSpawnTimer,
		SpawnIntervalSeconds,
		true,
		0.f  // fire immediately on start
	);
}

void UFarmPlantCollectibleSpawner::StopSpawning()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	}
}

void UFarmPlantCollectibleSpawner::SpawnCollectibleNow()
{
	if (!CollectibleClass)
	{
		return;
	}

	FBeamPlantData ResolvedPlant;
	if (!TryGetRandomPlantData(ResolvedPlant))
	{
		UE_LOG(LogTemp, Warning, TEXT("UFarmPlantCollectibleSpawner: failed to resolve any plant from PlantContentIds"));
		return;
	}

	FVector SpawnLocation;
	if (!TryPickSpawnPoint(SpawnLocation))
	{
		return;
	}

	FActorSpawnParameters Params;
	Params.Owner = GetOwner();
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const FTransform SpawnT(FRotator::ZeroRotator, SpawnLocation);
	ABeamFarmPlantCollectibleActor* Spawned = GetWorld()->SpawnActor<ABeamFarmPlantCollectibleActor>(CollectibleClass, SpawnT, Params);
	if (Spawned)
	{
		Spawned->SetPlantData(ResolvedPlant);
		Spawned->Quantity = QuantityPerCollectible;
		Spawned->OnPickedUp.AddDynamic(this, &UFarmPlantCollectibleSpawner::HandlePickedUp);
		ActiveCollectibles.Add(Spawned);
		OnPlantCollectibleSpawned(Spawned, SpawnT);
	}
}

// ─── Spawn point selection ────────────────────────────────────────────────────

bool UFarmPlantCollectibleSpawner::TryPickSpawnPoint(FVector& OutLocation)
{
	// Pre-compute total weight for weighted zone selection.
	float TotalWeight = 0.f;
	for (const FBeamFarmSpawnZone& Zone : SpawnZones)
	{
		TotalWeight += FMath::Max(Zone.Weight, 0.f);
	}

	for (int32 Attempt = 0; Attempt < MaxSpawnAttempts; ++Attempt)
	{
		FVector2D Candidate;

		if (SpawnZones.IsEmpty() || TotalWeight <= 0.f)
		{
			// Fallback: uniform random inside the base area.
			Candidate.X = FMath::RandRange(BaseAreaCenter.X - BaseAreaHalfExtents.X, BaseAreaCenter.X + BaseAreaHalfExtents.X);
			Candidate.Y = FMath::RandRange(BaseAreaCenter.Y - BaseAreaHalfExtents.Y, BaseAreaCenter.Y + BaseAreaHalfExtents.Y);
		}
		else
		{
			// Weighted zone selection: roll in [0, TotalWeight), subtract each zone's weight.
			float Roll = FMath::FRandRange(0.f, TotalWeight);
			const FBeamFarmSpawnZone* Selected = &SpawnZones.Last();
			for (const FBeamFarmSpawnZone& Zone : SpawnZones)
			{
				Roll -= FMath::Max(Zone.Weight, 0.f);
				if (Roll <= 0.f)
				{
					Selected = &Zone;
					break;
				}
			}

			Candidate.X = FMath::RandRange(Selected->Center.X - Selected->HalfExtents.X, Selected->Center.X + Selected->HalfExtents.X);
			Candidate.Y = FMath::RandRange(Selected->Center.Y - Selected->HalfExtents.Y, Selected->Center.Y + Selected->HalfExtents.Y);
		}

		if (IsPointExcluded(Candidate))
		{
			continue;
		}

		// Reject if too close to an already-active collectible.
		const FVector CandidateWorld(Candidate.X, Candidate.Y, SpawnZ);
		bool bTooClose = false;
		for (const ABeamFarmPlantCollectibleActor* Existing : ActiveCollectibles)
		{
			if (IsValid(Existing) && FVector::Dist2D(Existing->GetActorLocation(), CandidateWorld) < MinSpawnSeparation)
			{
				bTooClose = true;
				break;
			}
		}
		if (bTooClose)
		{
			continue;
		}

		OutLocation = CandidateWorld;
		return true;
	}

	return false;
}

bool UFarmPlantCollectibleSpawner::IsPointExcluded(const FVector2D& Point) const
{
	for (const FBeamFarmExclusionZone& Zone : ExclusionZones)
	{
		if (FMath::Abs(Point.X - Zone.Center.X) <= Zone.HalfExtents.X &&
			FMath::Abs(Point.Y - Zone.Center.Y) <= Zone.HalfExtents.Y)
		{
			return true;
		}
	}
	return false;
}

// ─── Content resolution ───────────────────────────────────────────────────────

bool UFarmPlantCollectibleSpawner::TryGetRandomPlantData(FBeamPlantData& OutData)
{
	if (PlantContentIds.IsEmpty())
	{
		return false;
	}

	if (!ContentSubsystem)
	{
		ContentSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UBeamContentSubsystem>();
		if (!ContentSubsystem)
		{
			return false;
		}
	}

	const int32 StartIdx = FMath::RandRange(0, PlantContentIds.Num() - 1);
	for (int32 Attempt = 0; Attempt < PlantContentIds.Num(); ++Attempt)
	{
		const FBeamContentId& ContentId = PlantContentIds[(StartIdx + Attempt) % PlantContentIds.Num()];

		UBeamPlantContent* PlantContent = nullptr;
		if (ContentSubsystem->TryGetContentOfType<UBeamPlantContent>(ContentId, PlantContent) && PlantContent)
		{
			OutData = PlantContent->PlantData;
			return true;
		}
	}

	return false;
}

// ─── Timer & pickup ───────────────────────────────────────────────────────────

void UFarmPlantCollectibleSpawner::OnSpawnTimer()
{
	ActiveCollectibles.RemoveAll([](const TObjectPtr<ABeamFarmPlantCollectibleActor>& C) { return !IsValid(C); });

	if (ActiveCollectibles.Num() >= MaxActiveCollectibles)
	{
		return;
	}

	SpawnCollectibleNow();
}

void UFarmPlantCollectibleSpawner::HandlePickedUp(ABeamFarmPlantCollectibleActor* Collectible, APawn* Collector)
{
	ActiveCollectibles.Remove(Collectible);
	OnPlantCollectibleCollected(Collectible, Collector, Collectible->PlantData, QuantityPerCollectible);
}

// ─── Debug drawing ────────────────────────────────────────────────────────────

void UFarmPlantCollectibleSpawner::DrawDebugZones()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	// Elevate slightly above SpawnZ so boxes are visible in a 2D-ish scene.
	const float DrawZ = SpawnZ + 20.f;
	const float BoxThickness = 3.f;
	const float HalfHeight = 10.f;  // thin flat box

	// Base area — blue, drawn only when SpawnZones is empty (it's the active fallback).
	if (SpawnZones.IsEmpty())
	{
		const FVector Center(BaseAreaCenter.X, BaseAreaCenter.Y, DrawZ);
		const FVector Extent(BaseAreaHalfExtents.X, BaseAreaHalfExtents.Y, HalfHeight);
		DrawDebugBox(World, Center, Extent, FColor::Blue, false, DebugDrawDuration, 0, BoxThickness);
		DrawDebugString(World, Center + FVector(0, 0, HalfHeight + 5.f), TEXT("BASE AREA"), nullptr, FColor::Cyan, DebugDrawDuration);
	}

	// Spawn zones — green, brightness proportional to weight.
	for (const FBeamFarmSpawnZone& Zone : SpawnZones)
	{
		const FVector Center(Zone.Center.X, Zone.Center.Y, DrawZ);
		const FVector Extent(Zone.HalfExtents.X, Zone.HalfExtents.Y, HalfHeight);

		// Map weight to green channel: weight 0 → dim (80), higher → brighter (max 255).
		const uint8 Green = (uint8)FMath::Clamp(FMath::RoundToInt(Zone.Weight * 60.f + 80.f), 80, 255);
		DrawDebugBox(World, Center, Extent, FColor(0, Green, 0), false, DebugDrawDuration, 0, BoxThickness);

		const FString Label = FString::Printf(TEXT("W: %.1f"), Zone.Weight);
		DrawDebugString(World, Center + FVector(0, 0, HalfHeight + 5.f), Label, nullptr, FColor::Green, DebugDrawDuration);
	}

	// Exclusion zones — red.
	for (const FBeamFarmExclusionZone& Zone : ExclusionZones)
	{
		const FVector Center(Zone.Center.X, Zone.Center.Y, DrawZ);
		const FVector Extent(Zone.HalfExtents.X, Zone.HalfExtents.Y, HalfHeight);
		DrawDebugBox(World, Center, Extent, FColor::Red, false, DebugDrawDuration, 0, BoxThickness);
		DrawDebugString(World, Center + FVector(0, 0, HalfHeight + 5.f), TEXT("EXCL"), nullptr, FColor::Red, DebugDrawDuration);
	}
}
