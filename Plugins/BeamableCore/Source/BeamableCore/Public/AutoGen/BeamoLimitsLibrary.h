
#pragma once

#include "CoreMinimal.h"
#include "BeamoLimits.h"

#include "BeamoLimitsLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamoLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize BeamoLimits To JSON String")
	static FString BeamoLimitsToJsonString(const UBeamoLimits* Serializable, const bool Pretty);		
};