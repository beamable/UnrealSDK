#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/MicroserviceRegistrationRequestBody.h"

#include "MicroserviceRegistrationRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMicroserviceRegistrationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="MicroserviceRegistrationRequestBody To JSON String")
	static FString MicroserviceRegistrationRequestBodyToJsonString(const UMicroserviceRegistrationRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make MicroserviceRegistrationRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bTrafficFilterEnabled, RoutingKey, Federation, Outer", NativeMakeFunc))
	static UMicroserviceRegistrationRequestBody* Make(FString ServiceName, FOptionalBool bTrafficFilterEnabled, FOptionalString RoutingKey, FOptionalArrayOfSupportedFederation Federation, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break MicroserviceRegistrationRequestBody", meta=(NativeBreakFunc))
	static void Break(const UMicroserviceRegistrationRequestBody* Serializable, FString& ServiceName, FOptionalBool& bTrafficFilterEnabled, FOptionalString& RoutingKey, FOptionalArrayOfSupportedFederation& Federation);
};