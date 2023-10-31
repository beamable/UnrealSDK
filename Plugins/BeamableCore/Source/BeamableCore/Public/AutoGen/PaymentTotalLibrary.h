#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PaymentTotal.h"

#include "PaymentTotalLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPaymentTotalLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - PaymentTotal To JSON String")
	static FString PaymentTotalToJsonString(const UPaymentTotal* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make PaymentTotal", meta=(DefaultToSelf="Outer", AdvancedDisplay="CurrencyCode, Outer", NativeMakeFunc))
	static UPaymentTotal* Make(int64 TotalRevenue, FOptionalString CurrencyCode, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break PaymentTotal", meta=(NativeBreakFunc))
	static void Break(const UPaymentTotal* Serializable, int64& TotalRevenue, FOptionalString& CurrencyCode);
};