
#pragma once

#include "CoreMinimal.h"
#include "RouteVariables.h"

#include "RouteVariablesLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URouteVariablesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RouteVariables To JSON String")
	static FString RouteVariablesToJsonString(const URouteVariables* Serializable, const bool Pretty);		
};