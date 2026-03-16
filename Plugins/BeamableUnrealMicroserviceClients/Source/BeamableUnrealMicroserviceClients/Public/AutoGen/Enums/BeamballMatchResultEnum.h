#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamballMatchResultEnum.generated.h"

UENUM(BlueprintType, Category="Beam|BeamballMs|Utils|Enums")
enum class EBeamballMatchResultEnum : uint8
{
	BEAM_Win UMETA(DisplayName="Win"),
	BEAM_Lose UMETA(DisplayName="Lose"),
	BEAM_Draw UMETA(DisplayName="Draw")		
};
