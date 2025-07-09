#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServiceRegistrationRequestBody.h"

#include "ServiceRegistrationRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServiceRegistrationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="ServiceRegistrationRequestBody To JSON String")
	static FString ServiceRegistrationRequestBodyToJsonString(const UServiceRegistrationRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ServiceRegistrationRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="RoutingKey, bTrafficFilterEnabled, Federation, Outer", NativeMakeFunc))
	static UServiceRegistrationRequestBody* Make(FOptionalString RoutingKey, FOptionalBool bTrafficFilterEnabled, FOptionalArrayOfSupportedFederation Federation, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break ServiceRegistrationRequestBody", meta=(NativeBreakFunc))
	static void Break(const UServiceRegistrationRequestBody* Serializable, FOptionalString& RoutingKey, FOptionalBool& bTrafficFilterEnabled, FOptionalArrayOfSupportedFederation& Federation);
};