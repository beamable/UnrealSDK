#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamBeamoV2RuleOperationType.generated.h"

UENUM(BlueprintType, Category="Beam|Beamo|Utils|Enums")
enum class EBeamBeamoV2RuleOperationType : uint8
{
	BEAM_Contain UMETA(DisplayName="Contain"),
	BEAM_NotContain UMETA(DisplayName="Not Contain")		
};
