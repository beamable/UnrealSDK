#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CompletePaymentRequestBody.h"

#include "CompletePaymentRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCompletePaymentRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Json", DisplayName="CompletePaymentRequestBody To JSON String")
	static FString CompletePaymentRequestBodyToJsonString(const UCompletePaymentRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Make/Break", DisplayName="Make CompletePaymentRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCompletePaymentRequestBody* Make(FString PaymentProvider, FString Receipt, FString PlayerId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Make/Break", DisplayName="Break CompletePaymentRequestBody", meta=(NativeBreakFunc))
	static void Break(const UCompletePaymentRequestBody* Serializable, FString& PaymentProvider, FString& Receipt, FString& PlayerId);
};