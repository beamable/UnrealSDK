#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamFriendSource.generated.h"

UENUM(BlueprintType, Category="Beam|Friends|Utils|Enums")
enum class EBeamFriendSource : uint8
{
	BEAM_native UMETA(DisplayName="Native"),
	BEAM_facebook UMETA(DisplayName="Facebook")		
};
