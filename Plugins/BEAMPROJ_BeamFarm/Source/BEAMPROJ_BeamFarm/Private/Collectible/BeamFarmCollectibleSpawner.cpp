// Copyright Beamable, Inc. All Rights Reserved.

#include "Collectible/BeamFarmCollectibleSpawner.h"
#include "DrawDebugHelpers.h"
#if WITH_EDITOR
#include "Components/LineBatchComponent.h"
#endif

// ─── Editor box helper ────────────────────────────────────────────────────────

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
		{0,1},{1,2},{2,3},{3,0},
		{4,5},{5,6},{6,7},{7,4},
		{0,4},{1,5},{2,6},{3,7},
	};
	for (const auto& E : Edges)
	{
		Batch->DrawLine(C[E[0]], C[E[1]], Color, 0, Thickness, -1.f);
	}
}
#endif

// ─── Constructor & lifecycle ──────────────────────────────────────────────────

UFarmCollectibleSpawner::UFarmCollectibleSpawner()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFarmCollectibleSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (SpawnerId.IsEmpty())
	{
		SpawnerId = FGuid::NewGuid().ToString(EGuidFormats::DigitsWithHyphens);
	}

	UBeamFarmSubsystem* Sub = GetWorld()->GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (!Sub)
	{
		return;
	}

	Sub->RegisterSpawner(BuildConfig());

	Sub->OnSpawnerCollectibleSpawned.AddDynamic(this, &UFarmCollectibleSpawner::HandleSubsystemCollectibleSpawned);
	Sub->OnSpawnerCollectibleCollected.AddDynamic(this, &UFarmCollectibleSpawner::HandleSubsystemCollectibleCollected);

	if (SpawnMode == EBeamFarmSpawnMode::WeightedZones && bDrawDebugZonesOnBeginPlay)
	{
		DrawDebugZones();
	}
}

void UFarmCollectibleSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UBeamFarmSubsystem* Sub = GetWorld()->GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (Sub)
	{
		Sub->UnregisterSpawner(SpawnerId);
		Sub->OnSpawnerCollectibleSpawned.RemoveDynamic(this, &UFarmCollectibleSpawner::HandleSubsystemCollectibleSpawned);
		Sub->OnSpawnerCollectibleCollected.RemoveDynamic(this, &UFarmCollectibleSpawner::HandleSubsystemCollectibleCollected);
	}

	Super::EndPlay(EndPlayReason);
}

void UFarmCollectibleSpawner::OnRegister()
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

void UFarmCollectibleSpawner::OnUnregister()
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
void UFarmCollectibleSpawner::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	UWorld* World = GetWorld();
	if (World && World->WorldType == EWorldType::Editor)
	{
		RebuildEditorVisualization();
	}
}

void UFarmCollectibleSpawner::RebuildEditorVisualization()
{
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

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

	const float DrawZ = SpawnZ + 10.f;
	const float BoxH  = 8.f;

	if (SpawnZones.IsEmpty())
	{
		BatchDrawBox(EditorLineBatch,
			FVector(BaseAreaCenter.X, BaseAreaCenter.Y, DrawZ),
			FVector(BaseAreaHalfExtents.X, BaseAreaHalfExtents.Y, BoxH),
			FLinearColor(0.2f, 0.4f, 1.f));
	}

	for (const FBeamFarmSpawnZone& Zone : SpawnZones)
	{
		const float T = FMath::Clamp(Zone.Weight / 5.f, 0.f, 1.f);
		BatchDrawBox(EditorLineBatch,
			FVector(Zone.Center.X, Zone.Center.Y, DrawZ),
			FVector(Zone.HalfExtents.X, Zone.HalfExtents.Y, BoxH),
			FLinearColor(0.f, 0.35f + 0.65f * T, 0.f));
	}

	for (const FBeamFarmExclusionZone& Zone : ExclusionZones)
	{
		BatchDrawBox(EditorLineBatch,
			FVector(Zone.Center.X, Zone.Center.Y, DrawZ),
			FVector(Zone.HalfExtents.X, Zone.HalfExtents.Y, BoxH),
			FLinearColor::Red);
	}
}
#endif

// ─── Subsystem pass-through helpers ──────────────────────────────────────────

void UFarmCollectibleSpawner::StartSpawning()
{
	UBeamFarmSubsystem* Sub = GetWorld()->GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (Sub)
	{
		Sub->StartSpawner(SpawnerId);
	}
}

void UFarmCollectibleSpawner::StopSpawning()
{
	UBeamFarmSubsystem* Sub = GetWorld()->GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (Sub)
	{
		Sub->StopSpawner(SpawnerId);
	}
}

void UFarmCollectibleSpawner::SpawnCollectibleNow()
{
	UBeamFarmSubsystem* Sub = GetWorld()->GetGameInstance()->GetSubsystem<UBeamFarmSubsystem>();
	if (Sub)
	{
		Sub->SpawnCollectibleForSpawner(SpawnerId);
	}
}

// ─── Debug drawing ────────────────────────────────────────────────────────────

void UFarmCollectibleSpawner::DrawDebugZones()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	const float DrawZ       = SpawnZ + 20.f;
	const float BoxThick    = 3.f;
	const float HalfHeight  = 10.f;

	if (SpawnZones.IsEmpty())
	{
		const FVector Center(BaseAreaCenter.X, BaseAreaCenter.Y, DrawZ);
		const FVector Extent(BaseAreaHalfExtents.X, BaseAreaHalfExtents.Y, HalfHeight);
		DrawDebugBox(World, Center, Extent, FColor::Blue, false, DebugDrawDuration, 0, BoxThick);
		DrawDebugString(World, Center + FVector(0, 0, HalfHeight + 5.f), TEXT("BASE AREA"), nullptr, FColor::Cyan, DebugDrawDuration);
	}

	for (const FBeamFarmSpawnZone& Zone : SpawnZones)
	{
		const FVector Center(Zone.Center.X, Zone.Center.Y, DrawZ);
		const FVector Extent(Zone.HalfExtents.X, Zone.HalfExtents.Y, HalfHeight);
		const uint8 G = (uint8)FMath::Clamp(FMath::RoundToInt(Zone.Weight * 60.f + 80.f), 80, 255);
		DrawDebugBox(World, Center, Extent, FColor(0, G, 0), false, DebugDrawDuration, 0, BoxThick);
		DrawDebugString(World, Center + FVector(0, 0, HalfHeight + 5.f),
			FString::Printf(TEXT("W: %.1f"), Zone.Weight), nullptr, FColor::Green, DebugDrawDuration);
	}

	for (const FBeamFarmExclusionZone& Zone : ExclusionZones)
	{
		const FVector Center(Zone.Center.X, Zone.Center.Y, DrawZ);
		const FVector Extent(Zone.HalfExtents.X, Zone.HalfExtents.Y, HalfHeight);
		DrawDebugBox(World, Center, Extent, FColor::Red, false, DebugDrawDuration, 0, BoxThick);
		DrawDebugString(World, Center + FVector(0, 0, HalfHeight + 5.f), TEXT("EXCL"), nullptr, FColor::Red, DebugDrawDuration);
	}
}

// ─── Internal ─────────────────────────────────────────────────────────────────

FBeamFarmSpawnConfig UFarmCollectibleSpawner::BuildConfig() const
{
	FBeamFarmSpawnConfig Config;
	Config.SpawnerId           = SpawnerId;
	Config.SpawnMode           = SpawnMode;
	Config.CollectibleClass    = CollectibleClass;
	Config.QuantityPerCollectible = QuantityPerCollectible;
	Config.SpawnIntervalSeconds   = SpawnIntervalSeconds;
	Config.MaxActiveCollectibles  = MaxActiveCollectibles;
	Config.MaterialData           = MaterialData;
	Config.SeedMaterialContentId  = SeedMaterialContentId;
	Config.SpawnTransforms        = SpawnTransforms;
	Config.PlantContentIds        = PlantContentIds;
	Config.SpawnZones             = SpawnZones;
	Config.ExclusionZones         = ExclusionZones;
	Config.BaseAreaCenter         = BaseAreaCenter;
	Config.BaseAreaHalfExtents    = BaseAreaHalfExtents;
	Config.SpawnZ                 = SpawnZ;
	Config.MinSpawnSeparation     = MinSpawnSeparation;
	Config.MaxSpawnAttempts       = MaxSpawnAttempts;
	return Config;
}

void UFarmCollectibleSpawner::HandleSubsystemCollectibleSpawned(const FString& InSpawnerId, ABeamFarmCollectibleActor* Collectible, const FTransform& SpawnTransform)
{
	if (InSpawnerId == SpawnerId)
	{
		OnCollectibleSpawned(Collectible, SpawnTransform);
	}
}

void UFarmCollectibleSpawner::HandleSubsystemCollectibleCollected(const FString& InSpawnerId, APawn* Collector, const FBeamFarmCollectibleInfo& Info)
{
	if (InSpawnerId == SpawnerId)
	{
		OnCollectibleCollected(Collector, Info);
	}
}
