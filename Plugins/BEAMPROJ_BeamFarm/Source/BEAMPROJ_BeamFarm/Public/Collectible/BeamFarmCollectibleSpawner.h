// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BeamSeedData.h"
#include "AutoGen/SubSystems/BeamBeamFarmMsApi.h"
#include "BeamFarmCollectibleSpawner.generated.h"

class ABeamFarmCollectibleActor;

/**
 * Component that periodically spawns ABeamFarmCollectibleActor instances at
 * designer-specified world transforms.
 *
 * Attach to any actor in the level (e.g. a GameManager or the Farm building actor).
 * Set CollectibleClass to a Blueprint subclass of ABeamFarmCollectibleActor.
 * Add entries to SpawnTransforms (world-space) in the Details panel.
 *
 * When a collectible is picked up, OnCollectibleCollected fires so Blueprint can
 * call the Beamable inventory subsystem to add the material to the player's account.
 *
 * SpawnTransforms is cycled round-robin: each spawn picks the next slot in the list
 * that has no active collectible sitting on it.
 */
UCLASS(ClassGroup = (BeamFarm), meta = (BlueprintSpawnableComponent))
class BEAMPROJ_BEAMFARM_API UFarmCollectibleSpawner : public UActorComponent
{
	GENERATED_BODY()

public:
	UFarmCollectibleSpawner();

	// Blueprint subclass of ABeamFarmCollectibleActor to spawn.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner")
	TSubclassOf<ABeamFarmCollectibleActor> CollectibleClass;

	// The seed this spawner produces. Assigned to ItemData on each spawn.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner")
	FBeamSeedData MaterialData;

	// Beamable content ID of the raw material currency this spawner grants
	// (e.g. "plant.raw.material.wheat"). Used by RegisterGroundItem on the server.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner")
	FString SeedMaterialContentId;

	// World-space transforms where collectibles may appear.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner")
	TArray<FTransform> SpawnTransforms;

	// How many seconds between spawn attempts.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner", meta = (ClampMin = "1.0"))
	float SpawnIntervalSeconds = 30.f;

	// Maximum number of collectibles alive simultaneously from this spawner.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner", meta = (ClampMin = "1"))
	int32 MaxActiveCollectibles = 5;

	// Beamable user slot used for RegisterGroundItem / CollectGroundItem calls.
	// Must match the UserSlotName on UFarmingComponent.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner")
	FString UserSlotName = TEXT("Player0");

	// Units of MaterialData granted per collectible.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Spawner", meta = (ClampMin = "1"))
	int32 QuantityPerCollectible = 1;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Spawner")
	void StartSpawning();

	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Spawner")
	void StopSpawning();

	// Force-spawn one collectible immediately (ignores MaxActiveCollectibles cap).
	UFUNCTION(BlueprintCallable, Category = "BeamFarm|Spawner")
	void SpawnCollectibleNow();

	// Override in Blueprint: called right after a new collectible is spawned.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Spawner")
	void OnCollectibleSpawned(ABeamFarmCollectibleActor* Collectible, const FTransform& SpawnTransform);

	// Override in Blueprint: call the Beamable inventory subsystem to add MaterialData to the player's account.
	UFUNCTION(BlueprintImplementableEvent, Category = "BeamFarm|Spawner")
	void OnCollectibleCollected(ABeamFarmCollectibleActor* Collectible, APawn* Collector, const FBeamSeedData& Material, int32 Quantity);

private:
	FTimerHandle SpawnTimerHandle;
	int32 NextSpawnIndex = 0;

	UPROPERTY()
	TArray<TObjectPtr<ABeamFarmCollectibleActor>> ActiveCollectibles;

	UPROPERTY()
	TObjectPtr<UBeamBeamFarmMsApi> BeamFarmMsApi;

	UFUNCTION()
	void OnSpawnTimer();

	UFUNCTION()
	void HandlePickedUp(ABeamFarmCollectibleActor* Collectible, APawn* Collector);
};
