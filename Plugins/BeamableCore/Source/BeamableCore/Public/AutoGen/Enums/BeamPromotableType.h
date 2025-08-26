#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamPromotableType.generated.h"

UENUM(BlueprintType, Category="Beam|Customer|Utils|Enums")
enum class EBeamPromotableType : uint8
{
	BEAM_Content UMETA(DisplayName="Content"),
	BEAM_Microservices UMETA(DisplayName="Microservices")		
};
