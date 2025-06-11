#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamWebhookServiceType.generated.h"

UENUM(BlueprintType, Category="Beam|Announcements|Utils|Enums")
enum class EBeamWebhookServiceType : uint8
{
	BEAM_UserMicroservice UMETA(DisplayName="User Microservice"),
	BEAM_ObjectService UMETA(DisplayName="Object Service"),
	BEAM_BasicService UMETA(DisplayName="Basic Service")		
};
