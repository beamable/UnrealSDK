#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DeleteRegistrationRequestBody.h"

#include "DeleteRegistrationRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDeleteRegistrationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="DeleteRegistrationRequestBody To JSON String")
	static FString DeleteRegistrationRequestBodyToJsonString(const UDeleteRegistrationRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make DeleteRegistrationRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="RoutingKey, Outer", NativeMakeFunc))
	static UDeleteRegistrationRequestBody* Make(FOptionalString RoutingKey, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break DeleteRegistrationRequestBody", meta=(NativeBreakFunc))
	static void Break(const UDeleteRegistrationRequestBody* Serializable, FOptionalString& RoutingKey);
};