#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamWebhookInvocationType.generated.h"

UENUM(BlueprintType, Category="Beam|Announcements|Utils|Enums")
enum class EBeamWebhookInvocationType : uint8
{
	BEAM_NonBlocking UMETA(DisplayName="Non Blocking"),
	BEAM_Blocking UMETA(DisplayName="Blocking")		
};
