#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RouteParameters.h"

#include "RouteParametersLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URouteParametersLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|4 - Json", DisplayName="RouteParameters To JSON String")
	static FString RouteParametersToJsonString(const URouteParameters* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|3 - Backend", DisplayName="Make RouteParameters", meta=(DefaultToSelf="Outer", AdvancedDisplay="Payload, ObjectId, Outer", NativeMakeFunc))
	static URouteParameters* Make(TArray<URouteParameter*> Parameters, FOptionalString Payload, FOptionalString ObjectId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Announcements|3 - Backend", DisplayName="Break RouteParameters", meta=(NativeBreakFunc))
	static void Break(const URouteParameters* Serializable, TArray<URouteParameter*>& Parameters, FOptionalString& Payload, FOptionalString& ObjectId);
};