// Copyright Beamable, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Collectible/BeamFarmCollectibleActor.h"
#include "BeamFarmPlantCollectibleActor.generated.h"

// Deprecated alias kept for Blueprint compatibility.
// New code should use ABeamFarmCollectibleActor directly.
UCLASS()
class BEAMPROJ_BEAMFARM_API ABeamFarmPlantCollectibleActor : public ABeamFarmCollectibleActor
{
	GENERATED_BODY()
};
