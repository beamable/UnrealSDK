#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PaymentResponse.h"

#include "PaymentResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPaymentResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Json", DisplayName="PaymentResponse To JSON String")
	static FString PaymentResponseToJsonString(const UPaymentResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Make/Break", DisplayName="Make PaymentResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="TransactionId, Outer", NativeMakeFunc))
	static UPaymentResponse* Make(FOptionalInt64 TransactionId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payment|Utils|Make/Break", DisplayName="Break PaymentResponse", meta=(NativeBreakFunc))
	static void Break(const UPaymentResponse* Serializable, FOptionalInt64& TransactionId);
};