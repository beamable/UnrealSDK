#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamBeamoV2LogLevel.generated.h"

UENUM(BlueprintType, Category="Beam|Beamo|Utils|Enums")
enum class EBeamBeamoV2LogLevel : uint8
{
	BEAM_Trace UMETA(DisplayName="Trace"),
	BEAM_Debug UMETA(DisplayName="Debug"),
	BEAM_Information UMETA(DisplayName="Information"),
	BEAM_Warning UMETA(DisplayName="Warning"),
	BEAM_Error UMETA(DisplayName="Error"),
	BEAM_Critical UMETA(DisplayName="Critical"),
	BEAM_None UMETA(DisplayName="None")		
};
