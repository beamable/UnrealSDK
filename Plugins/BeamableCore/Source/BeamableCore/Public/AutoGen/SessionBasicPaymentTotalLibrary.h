#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SessionBasicPaymentTotal.h"

#include "SessionBasicPaymentTotalLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USessionBasicPaymentTotalLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Json", DisplayName="SessionBasicPaymentTotal To JSON String")
	static FString SessionBasicPaymentTotalToJsonString(const USessionBasicPaymentTotal* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Make SessionBasicPaymentTotal", meta=(DefaultToSelf="Outer", AdvancedDisplay="CurrencyCode, Outer", NativeMakeFunc))
	static USessionBasicPaymentTotal* Make(int64 TotalRevenue, FOptionalString CurrencyCode, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Make/Break", DisplayName="Break SessionBasicPaymentTotal", meta=(NativeBreakFunc))
	static void Break(const USessionBasicPaymentTotal* Serializable, int64& TotalRevenue, FOptionalString& CurrencyCode);
};