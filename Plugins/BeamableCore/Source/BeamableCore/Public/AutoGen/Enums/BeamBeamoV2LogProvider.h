#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonUtils.h"

#include "BeamBeamoV2LogProvider.generated.h"

UENUM(BlueprintType, Category="Beam|Beamo|Utils|Enums")
enum class EBeamBeamoV2LogProvider : uint8
{
	BEAM_Cloudwatch UMETA(DisplayName="Cloudwatch"),
	BEAM_Clickhouse UMETA(DisplayName="Clickhouse")		
};
