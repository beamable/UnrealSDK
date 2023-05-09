#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RouteVariables.h"

#include "RouteVariablesLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URouteVariablesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - RouteVariables To JSON String")
	static FString RouteVariablesToJsonString(const URouteVariables* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make RouteVariables", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URouteVariables* Make(TArray<URouteVariable*> Variables, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break RouteVariables", meta=(NativeBreakFunc))
	static void Break(const URouteVariables* Serializable, TArray<URouteVariable*>& Variables);
};