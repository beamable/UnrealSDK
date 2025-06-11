#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamLobbyRestriction.generated.h"

UENUM(BlueprintType, Category="Beam|Lobby|Utils|Enums")
enum class EBeamLobbyRestriction : uint8
{
	BEAM_Null UMETA(DisplayName="Null"),
	BEAM_Closed UMETA(DisplayName="Closed"),
	BEAM_Open UMETA(DisplayName="Open")		
};
