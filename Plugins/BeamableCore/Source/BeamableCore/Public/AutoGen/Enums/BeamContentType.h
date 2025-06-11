#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamContentType.generated.h"

UENUM(BlueprintType, Category="Beam|Content|Utils|Enums")
enum class EBeamContentType : uint8
{
	BEAM_content UMETA(DisplayName="Content"),
	BEAM_text UMETA(DisplayName="Text"),
	BEAM_binary UMETA(DisplayName="Binary")		
};
