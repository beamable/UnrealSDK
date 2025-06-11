#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamInvitationDirection.generated.h"

UENUM(BlueprintType, Category="Beam|Friends|Utils|Enums")
enum class EBeamInvitationDirection : uint8
{
	BEAM_incoming UMETA(DisplayName="Incoming"),
	BEAM_outgoing UMETA(DisplayName="Outgoing")		
};
