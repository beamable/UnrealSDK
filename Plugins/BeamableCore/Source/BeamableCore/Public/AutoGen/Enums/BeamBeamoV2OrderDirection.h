#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamBeamoV2OrderDirection.generated.h"

UENUM(BlueprintType, Category="Beam|Beamo|Utils|Enums")
enum class EBeamBeamoV2OrderDirection : uint8
{
	BEAM_Desc UMETA(DisplayName="Desc"),
	BEAM_Asc UMETA(DisplayName="Asc")		
};
