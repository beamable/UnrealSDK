#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RouteVariable.h"

#include "RouteVariableLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URouteVariableLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Json", DisplayName="RouteVariable To JSON String")
	static FString RouteVariableToJsonString(const URouteVariable* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Make RouteVariable", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static URouteVariable* Make(FString Name, FString TypeName, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Make/Break", DisplayName="Break RouteVariable", meta=(NativeBreakFunc))
	static void Break(const URouteVariable* Serializable, FString& Name, FString& TypeName);
};