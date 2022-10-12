
#pragma once

#include "CoreMinimal.h"
#include "RouteParameter.h"

#include "RouteParameterLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URouteParameterLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RouteParameter To JSON String")
	static FString RouteParameterToJsonString(const URouteParameter* Serializable, const bool Pretty);		
};