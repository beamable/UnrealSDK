// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Collectible/BeamFarmCollectibleSpawner.h"
#include "FarmPlantCollectibleSpawner.generated.h"

// Deprecated alias kept for Blueprint compatibility.
// New code should use UFarmCollectibleSpawner with SpawnMode = WeightedZones directly.
UCLASS()
class BEAMPROJ_BEAMFARM_API UFarmPlantCollectibleSpawner : public UFarmCollectibleSpawner
{
	GENERATED_BODY()
};
