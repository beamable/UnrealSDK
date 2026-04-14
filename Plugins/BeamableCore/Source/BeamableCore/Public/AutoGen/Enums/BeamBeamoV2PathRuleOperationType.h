#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamBeamoV2PathRuleOperationType.generated.h"

UENUM(BlueprintType, Category="Beam|Beamo|Utils|Enums")
enum class EBeamBeamoV2PathRuleOperationType : uint8
{
	BEAM_Include UMETA(DisplayName="Include"),
	BEAM_Contain UMETA(DisplayName="Contain"),
	BEAM_StartsWith UMETA(DisplayName="Starts With"),
	BEAM_EndsWith UMETA(DisplayName="Ends With")		
};
