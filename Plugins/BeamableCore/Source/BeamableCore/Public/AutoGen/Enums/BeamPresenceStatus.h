#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamPresenceStatus.generated.h"

UENUM(BlueprintType, Category="Beam|Presence|Utils|Enums")
enum class EBeamPresenceStatus : uint8
{
	BEAM_Visible UMETA(DisplayName="Visible"),
	BEAM_Invisible UMETA(DisplayName="Invisible"),
	BEAM_Dnd UMETA(DisplayName="Dnd"),
	BEAM_Away UMETA(DisplayName="Away")		
};
