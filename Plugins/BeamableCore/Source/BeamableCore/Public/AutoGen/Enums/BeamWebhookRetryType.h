#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamWebhookRetryType.generated.h"

UENUM(BlueprintType, Category="Beam|Announcements|Utils|Enums")
enum class EBeamWebhookRetryType : uint8
{
	BEAM_None UMETA(DisplayName="None"),
	BEAM_Once UMETA(DisplayName="Once"),
	BEAM_ExponentialBackoff UMETA(DisplayName="Exponential Backoff")		
};
