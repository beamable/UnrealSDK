#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CurrencyChange.h"

#include "CurrencyChangeLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCurrencyChangeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - CurrencyChange To JSON String")
	static FString CurrencyChangeToJsonString(const UCurrencyChange* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make CurrencyChange", meta=(DefaultToSelf="Outer", AdvancedDisplay="OriginalAmount, Outer", NativeMakeFunc))
	static UCurrencyChange* Make(FString Symbol, int64 Amount, FOptionalInt64 OriginalAmount, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break CurrencyChange", meta=(NativeBreakFunc))
	static void Break(const UCurrencyChange* Serializable, FString& Symbol, int64& Amount, FOptionalInt64& OriginalAmount);
};