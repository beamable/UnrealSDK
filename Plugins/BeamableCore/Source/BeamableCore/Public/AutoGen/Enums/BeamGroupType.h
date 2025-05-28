#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamGroupType.generated.h"

UENUM(BlueprintType, Category="Beam|GroupUsers|Utils|Enums")
enum class EBeamGroupType : uint8
{
	BEAM_guild UMETA(DisplayName="Guild"),
	BEAM_subgroup UMETA(DisplayName="Subgroup")		
};
