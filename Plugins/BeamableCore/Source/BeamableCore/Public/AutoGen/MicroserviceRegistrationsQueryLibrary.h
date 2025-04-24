#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MicroserviceRegistrationsQuery.h"

#include "MicroserviceRegistrationsQueryLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMicroserviceRegistrationsQueryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="MicroserviceRegistrationsQuery To JSON String")
	static FString MicroserviceRegistrationsQueryToJsonString(const UMicroserviceRegistrationsQuery* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make MicroserviceRegistrationsQuery", meta=(DefaultToSelf="Outer", AdvancedDisplay="bLocalOnly, ServiceName, RoutingKey, Federation, Outer", NativeMakeFunc))
	static UMicroserviceRegistrationsQuery* Make(FOptionalBool bLocalOnly, FOptionalString ServiceName, FOptionalString RoutingKey, FOptionalSupportedFederation Federation, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break MicroserviceRegistrationsQuery", meta=(NativeBreakFunc))
	static void Break(const UMicroserviceRegistrationsQuery* Serializable, FOptionalBool& bLocalOnly, FOptionalString& ServiceName, FOptionalString& RoutingKey, FOptionalSupportedFederation& Federation);
};