// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BeamPlantData.h"
#include "BeamBackend/SemanticTypes/BeamContentId.h"
#include "FarmPlantCollectibleSpawner.generated.h"

class ABeamFarmPlantCollectibleActor;
class UBeamContentSubsystem;
class ULineBatchComponent;

// ─── Zone data structures ────────────────────────────────────────────────────

/**
 * A weighted rectangular area (world-space XY) from which spawn candidates are drawn.
 * Higher Weight values make this zone more likely to be selected relative to other zones.
 */
USTRUCT(BlueprintType)
struct BEAMPROJ_BEAMFARM_API FBeamFarmSpawnZone
{
	GENERATED_BODY()

	// World-space XY center of this zone.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone")
	FVector2D Center = FVector2D::ZeroVector;

	// Half-extents (half-width, half-height) of the rectangle.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone", meta = (ClampMin = "1.0"))
	FVector2D HalfExtents = FVector2D(200.f, 200.f);

	// Relative probability weight. 0 disables this zone.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone", meta = (ClampMin = "0.0"))
	float Weight = 1.f;
};

/**
 * A rectangular area (world-space XY) where spawning is blocked.
 */
USTRUCT(BlueprintType)
struct BEAMPROJ_BEAMFARM_API FBeamFarmExclusionZone
{
	GENERATED_BODY()

	// World-space XY center of this zone.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone")
	FVector2D Center = FVector2D::ZeroVector;

	// Half-extents (half-width, half-height) of the rectangle.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zone", meta = (ClampMin = "1.0"))
	FVector2D HalfExtents = FVector2D(100.f, 100.f);
};

// ─── Spawner component ───────────────────────────────────────────────────────

/**
 * Component that periodically spawns ABeamFarmPlantCollectibleActor instances.
 *
 * Spawn placement uses three layers:
 *   1. SpawnZones — weighted rectangles where items prefer to appear.
 *      Each spawn attempt picks a zone by weighted random, then a random point inside it.
 *   2. ExclusionZones — rectangles that block any spawn point that falls inside them.
 *   3. Fallback — if SpawnZones is empty, a random point inside BaseArea is used instead.
 *
 * The item type is picked randomly from PlantContentIds each spawn and resolved via the
 * Beamable content system.
 *
 * Call DrawDebugZones() or enable bDrawDebugZonesOnBeginPlay to visualize zones:
 *   Green = spawn zones (brighter = higher weight)  |  Red = exclusion zones  |  Blue = base area
 */
UCLASS(ClassGroup = (BeamFarm), meta = (BlueprintSpawnableComponent))
class BEAMPROJ_BEAMFARM_API UFarmPlantCollectibleSpawner : public UActorComponent
{
	GENERATED_BODY()

public:
	UFarmPlantCollectibleSpawner();

	// ── Item configuration ─────────────────────────────────────────────────

	// Blueprint subclass of ABeamFarmPlantCollectibleActor to spawn.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner")
	TSubclassOf<ABeamFarmPlantCollectibleActor> CollectibleClass;

	// Beamable content IDs of the plant types this spawner can produce (e.g. "itemplant.wheat").
	// A random entry is resolved from the content system on each spawn.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner")
	TArray<FBeamContentId> PlantContentIds;

	// Units granted to the player per collectible pick-up.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner", meta = (ClampMin = "1"))
	int32 QuantityPerCollectible = 1;

	// ── Timing ────────────────────────────────────────────────────────────

	// Seconds between spawn attempts.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner", meta = (ClampMin = "1.0"))
	float SpawnIntervalSeconds = 30.f;

	// Maximum number of collectibles alive simultaneously from this spawner.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner", meta = (ClampMin = "1"))
	int32 MaxActiveCollectibles = 5;

	// ── Spawn zones ────────────────────────────────────────────────────────

	// Weighted rectangles where spawn candidates are drawn. If empty, BaseArea is used.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|Zones")
	TArray<FBeamFarmSpawnZone> SpawnZones;

	// Rectangles that block any spawn candidate falling inside them.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|Zones")
	TArray<FBeamFarmExclusionZone> ExclusionZones;

	// Fallback spawn area used when SpawnZones is empty. Random point inside this rect.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|Zones")
	FVector2D BaseAreaCenter = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|Zones", meta = (ClampMin = "1.0"))
	FVector2D BaseAreaHalfExtents = FVector2D(500.f, 500.f);

	// Z height at which collectibles are spawned.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|Zones")
	float SpawnZ = 0.f;

	// Minimum distance (cm) between any two active collectibles.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|Zones", meta = (ClampMin = "0.0"))
	float MinSpawnSeparation = 80.f;

	// Maximum point-picking attempts per spawn call before giving up.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|Zones", meta = (ClampMin = "1"))
	int32 MaxSpawnAttempts = 20;

	// ── Debug ─────────────────────────────────────────────────────────────

	// Draw zone outlines automatically when the game starts.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|Debug")
	bool bDrawDebugZonesOnBeginPlay = false;

	// How long drawn zone shapes persist (seconds). Use -1 for persistent until next call.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner|Debug")
	float DebugDrawDuration = 60.f;

	// ── Interface ─────────────────────────────────────────────────────────

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	virtual void OnRegister() override;
	virtual void OnUnregister() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Spawner")
	void StartSpawning();

	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Spawner")
	void StopSpawning();

	// Force-spawn one collectible immediately (ignores MaxActiveCollectibles cap).
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Spawner")
	void SpawnCollectibleNow();

	/**
	 * Draw all configured zones in the viewport for inspection.
	 *   Green box  = spawn zone  (label shows weight)
	 *   Red box    = exclusion zone
	 *   Blue box   = base area (shown only when SpawnZones is empty)
	 * Shapes persist for DebugDrawDuration seconds.
	 */
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Spawner|Debug")
	void DrawDebugZones();

	// Override in Blueprint: called right after a new collectible is spawned.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Spawner")
	void OnPlantCollectibleSpawned(ABeamFarmPlantCollectibleActor* Collectible, const FTransform& SpawnTransform);

	// Override in Blueprint: call the Beamable inventory subsystem to add Plant to the player's account.
	// Plant is the resolved content data for the specific item that was collected.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Spawner")
	void OnPlantCollectibleCollected(ABeamFarmPlantCollectibleActor* Collectible, APawn* Collector, const FBeamPlantData& Plant, int32 Quantity);

private:
	FTimerHandle SpawnTimerHandle;

	UPROPERTY()
	TArray<TObjectPtr<ABeamFarmPlantCollectibleActor>> ActiveCollectibles;

	UPROPERTY()
	TObjectPtr<UBeamContentSubsystem> ContentSubsystem;

	// Picks a random spawn point respecting zones, exclusions, and separation.
	// Returns false if no valid point is found within MaxSpawnAttempts tries.
	bool TryPickSpawnPoint(FVector& OutLocation);

	// Returns true if Point falls inside any exclusion zone.
	bool IsPointExcluded(const FVector2D& Point) const;

	// Picks a random entry from PlantContentIds and resolves it via the content system.
	// Tries every entry (starting at a random index) before returning false.
	bool TryGetRandomPlantData(FBeamPlantData& OutData);

	UFUNCTION()
	void OnSpawnTimer();

	UFUNCTION()
	void HandlePickedUp(ABeamFarmPlantCollectibleActor* Collectible, APawn* Collector);

#if WITH_EDITORONLY_DATA
	// Line batch component used to draw zone outlines in the editor viewport.
	// Recreated whenever zone properties change. Hidden in game.
	UPROPERTY(Transient)
	TObjectPtr<ULineBatchComponent> EditorLineBatch;
#endif

#if WITH_EDITOR
	void RebuildEditorVisualization();
#endif
};
