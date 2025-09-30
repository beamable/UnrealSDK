#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamActivationStatus.generated.h"

UENUM(BlueprintType, Category="Beam|Customer|Utils|Enums")
enum class EBeamActivationStatus : uint8
{
	BEAM_Pending UMETA(DisplayName="Pending"),
	BEAM_Activated UMETA(DisplayName="Activated")		
};
