#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamBeamoV2PlayerRuleOperationType.generated.h"

UENUM(BlueprintType, Category="Beam|Beamo|Utils|Enums")
enum class EBeamBeamoV2PlayerRuleOperationType : uint8
{
	BEAM_Include UMETA(DisplayName="Include"),
	BEAM_GreaterThan UMETA(DisplayName="Greater Than"),
	BEAM_LesserThan UMETA(DisplayName="Lesser Than")		
};
