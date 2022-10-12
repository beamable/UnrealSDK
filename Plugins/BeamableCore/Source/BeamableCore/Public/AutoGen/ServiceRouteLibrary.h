
#pragma once

#include "CoreMinimal.h"
#include "ServiceRoute.h"

#include "ServiceRouteLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UServiceRouteLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize ServiceRoute To JSON String")
	static FString ServiceRouteToJsonString(const UServiceRoute* Serializable, const bool Pretty);		
};