
#pragma once

#include "CoreMinimal.h"
#include "RouteVariable.h"

#include "RouteVariableLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API URouteVariableLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize RouteVariable To JSON String")
	static FString RouteVariableToJsonString(const URouteVariable* Serializable, const bool Pretty);		
};