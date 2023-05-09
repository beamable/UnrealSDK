#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RouteParameter.h"

#include "RouteParameterLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URouteParameterLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - RouteParameter To JSON String")
	static FString RouteParameterToJsonString(const URouteParameter* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make RouteParameter", meta=(DefaultToSelf="Outer", AdvancedDisplay="VariableRef, Outer", NativeMakeFunc))
	static URouteParameter* Make(FString Name, FString Body, FString TypeName, FOptionalVariableReference VariableRef, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break RouteParameter", meta=(NativeBreakFunc))
	static void Break(const URouteParameter* Serializable, FString& Name, FString& Body, FString& TypeName, FOptionalVariableReference& VariableRef);
};