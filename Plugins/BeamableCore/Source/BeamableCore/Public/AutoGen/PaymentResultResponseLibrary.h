#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PaymentResultResponse.h"

#include "PaymentResultResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPaymentResultResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Json", DisplayName="PaymentResultResponse To JSON String")
	static FString PaymentResultResponseToJsonString(const UPaymentResultResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make PaymentResultResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPaymentResultResponse* Make(FString Result, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Break PaymentResultResponse", meta=(NativeBreakFunc))
	static void Break(const UPaymentResultResponse* Serializable, FString& Result);
};