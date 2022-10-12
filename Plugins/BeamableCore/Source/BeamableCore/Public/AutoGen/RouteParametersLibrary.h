
#pragma once

#include "CoreMinimal.h"
#include "RouteParameters.h"

#include "RouteParametersLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URouteParametersLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RouteParameters To JSON String")
	static FString RouteParametersToJsonString(const URouteParameters* Serializable, const bool Pretty);		
};