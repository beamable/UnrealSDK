#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PaymentTotal.h"

#include "PaymentTotalLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPaymentTotalLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Json", DisplayName="PaymentTotal To JSON String")
	static FString PaymentTotalToJsonString(const UPaymentTotal* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Make PaymentTotal", meta=(DefaultToSelf="Outer", AdvancedDisplay="CurrencyCode, Outer", NativeMakeFunc))
	static UPaymentTotal* Make(int64 TotalRevenue, FOptionalString CurrencyCode, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Break PaymentTotal", meta=(NativeBreakFunc))
	static void Break(const UPaymentTotal* Serializable, int64& TotalRevenue, FOptionalString& CurrencyCode);
};