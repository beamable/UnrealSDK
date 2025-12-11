#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UpdatePaymentRequestBody.h"

#include "UpdatePaymentRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUpdatePaymentRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Json", DisplayName="UpdatePaymentRequestBody To JSON String")
	static FString UpdatePaymentRequestBodyToJsonString(const UUpdatePaymentRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Make/Break", DisplayName="Make UpdatePaymentRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Reason, Outer", NativeMakeFunc))
	static UUpdatePaymentRequestBody* Make(EBeamTransactionState State, FOptionalString Reason, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Make/Break", DisplayName="Break UpdatePaymentRequestBody", meta=(NativeBreakFunc))
	static void Break(const UUpdatePaymentRequestBody* Serializable, EBeamTransactionState& State, FOptionalString& Reason);
};