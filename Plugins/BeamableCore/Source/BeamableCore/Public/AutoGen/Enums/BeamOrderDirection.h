#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamOrderDirection.generated.h"

UENUM(BlueprintType, Category="Beam|Beamo|Utils|Enums")
enum class EBeamOrderDirection : uint8
{
	BEAM_Desc UMETA(DisplayName="Desc"),
	BEAM_Asc UMETA(DisplayName="Asc")		
};
