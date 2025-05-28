#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamEventState.generated.h"

UENUM(BlueprintType, Category="Beam|Events|Utils|Enums")
enum class EBeamEventState : uint8
{
	BEAM_running UMETA(DisplayName="Running"),
	BEAM_unknown UMETA(DisplayName="Unknown"),
	BEAM_cancelled UMETA(DisplayName="Cancelled"),
	BEAM_done UMETA(DisplayName="Done"),
	BEAM_pending UMETA(DisplayName="Pending")		
};
