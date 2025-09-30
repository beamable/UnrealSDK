#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamPaymentStatus.generated.h"

UENUM(BlueprintType, Category="Beam|Customer|Utils|Enums")
enum class EBeamPaymentStatus : uint8
{
	BEAM_Free UMETA(DisplayName="Free"),
	BEAM_Paid UMETA(DisplayName="Paid"),
	BEAM_Banned UMETA(DisplayName="Banned")		
};
