#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServiceRegistrationQuery.h"

#include "ServiceRegistrationQueryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServiceRegistrationQueryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="ServiceRegistrationQuery To JSON String")
	static FString ServiceRegistrationQueryToJsonString(const UServiceRegistrationQuery* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ServiceRegistrationQuery", meta=(DefaultToSelf="Outer", AdvancedDisplay="bLocalOnly, ServiceName, RoutingKey, Federation, Outer", NativeMakeFunc))
	static UServiceRegistrationQuery* Make(FOptionalBool bLocalOnly, FOptionalString ServiceName, FOptionalString RoutingKey, FOptionalSupportedFederation Federation, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break ServiceRegistrationQuery", meta=(NativeBreakFunc))
	static void Break(const UServiceRegistrationQuery* Serializable, FOptionalBool& bLocalOnly, FOptionalString& ServiceName, FOptionalString& RoutingKey, FOptionalSupportedFederation& Federation);
};