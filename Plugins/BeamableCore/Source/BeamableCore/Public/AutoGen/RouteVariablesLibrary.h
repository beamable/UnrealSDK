#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RouteVariables.h"

#include "RouteVariablesLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URouteVariablesLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Json", DisplayName="RouteVariables To JSON String")
	static FString RouteVariablesToJsonString(const URouteVariables* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make RouteVariables", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URouteVariables* Make(TArray<URouteVariable*> Variables, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Break RouteVariables", meta=(NativeBreakFunc))
	static void Break(const URouteVariables* Serializable, TArray<URouteVariable*>& Variables);
};