#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamContentVisibility.generated.h"

UENUM(BlueprintType, Category="Beam|Content|Utils|Enums")
enum class EBeamContentVisibility : uint8
{
	BEAM_public UMETA(DisplayName="Public"),
	BEAM_private UMETA(DisplayName="Private")		
};
