#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CurrencyView.h"

#include "CurrencyViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCurrencyViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="CurrencyView To JSON String")
	static FString CurrencyViewToJsonString(const UCurrencyView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make CurrencyView", meta=(DefaultToSelf="Outer", AdvancedDisplay="Proxy, Outer", NativeMakeFunc))
	static UCurrencyView* Make(FString Id, int64 Amount, TArray<UCurrencyProperty*> Properties, FOptionalFederationInfo Proxy, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break CurrencyView", meta=(NativeBreakFunc))
	static void Break(const UCurrencyView* Serializable, FString& Id, int64& Amount, TArray<UCurrencyProperty*>& Properties, FOptionalFederationInfo& Proxy);
};