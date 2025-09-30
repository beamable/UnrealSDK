#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UpdateCustomerRequestBody.h"

#include "UpdateCustomerRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUpdateCustomerRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Json", DisplayName="UpdateCustomerRequestBody To JSON String")
	static FString UpdateCustomerRequestBodyToJsonString(const UUpdateCustomerRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Make UpdateCustomerRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="PaymentStatus, Outer", NativeMakeFunc))
	static UUpdateCustomerRequestBody* Make(FOptionalPaymentStatus PaymentStatus, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Make/Break", DisplayName="Break UpdateCustomerRequestBody", meta=(NativeBreakFunc))
	static void Break(const UUpdateCustomerRequestBody* Serializable, FOptionalPaymentStatus& PaymentStatus);
};