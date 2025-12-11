#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeginPaymentRequestBody.h"

#include "BeginPaymentRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeginPaymentRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Json", DisplayName="BeginPaymentRequestBody To JSON String")
	static FString BeginPaymentRequestBodyToJsonString(const UBeginPaymentRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Make/Break", DisplayName="Make BeginPaymentRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="InitHistoryData, Outer", NativeMakeFunc))
	static UBeginPaymentRequestBody* Make(FString PlayerId, FString PaymentProvider, UTransactionDetails* Details, FOptionalString InitHistoryData, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Make/Break", DisplayName="Break BeginPaymentRequestBody", meta=(NativeBreakFunc))
	static void Break(const UBeginPaymentRequestBody* Serializable, FString& PlayerId, FString& PaymentProvider, UTransactionDetails*& Details, FOptionalString& InitHistoryData);
};