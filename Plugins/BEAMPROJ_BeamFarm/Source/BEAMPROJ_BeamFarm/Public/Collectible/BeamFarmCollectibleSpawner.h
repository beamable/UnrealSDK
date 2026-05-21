// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BeamSeedData.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "Farming/FarmTypes.h"
#include "Subsystem/BeamFarmSubsystem.h"
#include "BeamFarmCollectibleSpawner.generated.h"

class ABeamFarmCollectibleActor;
class ULineBatchComponent;

/**
 * Data component that configures a collectible spawner and registers it with UBeamFarmSubsystem.
 *
 * All spawn timing, actor management, and content resolution are handled by the subsystem.
 * This component's sole responsibilities are:
 *   1. Holding the designer-authored spawn configuration (set in the Details panel).
 *   2. Calling UBeamFarmSubsystem::RegisterSpawner on BeginPlay and UnregisterSpawner on EndPlay.
 *   3. Subscribing to the subsystem's per-spawner delegates and forwarding them to
 *      BlueprintImplementableEvents so Blueprint subclasses can react per-spawner.
 *
 * Supports two spawn modes (EBeamFarmSpawnMode, defined in FarmTypes.h):
 *   FixedTransforms — round-robin across designer-placed world-space transforms.
 *   WeightedZones   — random placement using weighted rectangles and exclusion zones.
 *
 * Attach to any actor in the level. Set CollectibleClass to a Blueprint subclass of
 * ABeamFarmCollectibleActor. Assign a unique SpawnerId or leave it empty to auto-generate one.
 */
UCLASS(ClassGroup = (BeamFarm), meta = (BlueprintSpawnableComponent))
class BEAMPROJ_BEAMFARM_API UFarmCollectibleSpawner : public UActorComponent
{
	GENERATED_BODY()

public:
	UFarmCollectibleSpawner();

	// ── Identity ──────────────────────────────────────────────────────────

	// Unique identifier for this spawner used to route subsystem events.
	// Auto-generated on BeginPlay if left empty; assign manually when scripting
	// StartSpawner / StopSpawner / SpawnCollectibleForSpawner from Blueprint.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner")
	FString SpawnerId;

	// ── Common ─────────────────────────────────────────────────────────────

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner")
	EBeamFarmSpawnMode SpawnMode = EBeamFarmSpawnMode::FixedTransforms;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner")
	TSubclassOf<ABeamFarmCollectibleActor> CollectibleClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner", meta = (ClampMin = "1"))
	int32 QuantityPerCollectible = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner", meta = (ClampMin = "1.0"))
	float SpawnIntervalSeconds = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner", meta = (ClampMin = "1"))
	int32 MaxActiveCollectibles = 5;

	// ── FixedTransforms mode ───────────────────────────────────────────────

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|FixedTransforms")
	FBeamSeedData MaterialData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|FixedTransforms")
	FString SeedMaterialContentId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|FixedTransforms")
	TArray<FTransform> SpawnTransforms;

	// ── WeightedZones mode ─────────────────────────────────────────────────

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|WeightedZones")
	TArray<FBeamContentId> PlantContentIds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|WeightedZones")
	TArray<FBeamFarmSpawnZone> SpawnZones;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|WeightedZones")
	TArray<FBeamFarmExclusionZone> ExclusionZones;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|WeightedZones")
	FVector2D BaseAreaCenter = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|WeightedZones", meta = (ClampMin = "1.0"))
	FVector2D BaseAreaHalfExtents = FVector2D(500.f, 500.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|WeightedZones")
	float SpawnZ = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|WeightedZones", meta = (ClampMin = "0.0"))
	float MinSpawnSeparation = 80.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|WeightedZones", meta = (ClampMin = "1"))
	int32 MaxSpawnAttempts = 20;

	// ── Debug ──────────────────────────────────────────────────────────────

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|Debug")
	bool bDrawDebugZonesOnBeginPlay = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|Debug")
	float DebugDrawDuration = 60.f;

	// ── Subsystem pass-through helpers ─────────────────────────────────────

	// Start the spawn timer after it was stopped (calls UBeamFarmSubsystem::StartSpawner).
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Spawner")
	void StartSpawning();

	// Stop the spawn timer without destroying active collectibles.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Spawner")
	void StopSpawning();

	// Force one immediate spawn, ignoring the MaxActiveCollectibles cap.
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Spawner")
	void SpawnCollectibleNow();

	// Draw zone outlines for designer inspection (WeightedZones mode, editor only).
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Spawner|Debug")
	void DrawDebugZones();

	// Override in Blueprint: called right after a new collectible for this spawner is spawned.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Spawner")
	void OnCollectibleSpawned(ABeamFarmCollectibleActor* Collectible, const FTransform& SpawnTransform);

	// Override in Blueprint: called after a collectible for this spawner is collected.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Spawner")
	void OnCollectibleCollected(APawn* Collector, const FBeamFarmCollectibleInfo& Info);

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	virtual void OnRegister() override;
	virtual void OnUnregister() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	FBeamFarmSpawnConfig BuildConfig() const;

	UFUNCTION()
	void HandleSubsystemCollectibleSpawned(const FString& InSpawnerId, ABeamFarmCollectibleActor* Collectible, const FTransform& SpawnTransform);

	UFUNCTION()
	void HandleSubsystemCollectibleCollected(const FString& InSpawnerId, APawn* Collector, const FBeamFarmCollectibleInfo& Info);

#if WITH_EDITORONLY_DATA
	UPROPERTY(Transient)
	TObjectPtr<ULineBatchComponent> EditorLineBatch;
#endif

#if WITH_EDITOR
	void RebuildEditorVisualization();
#endif
};
