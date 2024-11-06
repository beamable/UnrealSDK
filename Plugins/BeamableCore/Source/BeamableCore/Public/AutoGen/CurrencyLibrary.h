#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Currency.h"

#include "CurrencyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCurrencyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - Currency To JSON String")
	static FString CurrencyToJsonString(const UCurrency* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make Currency", meta=(DefaultToSelf="Outer", AdvancedDisplay="UpdatedAt, Proxy, Properties, Outer", NativeMakeFunc))
	static UCurrency* Make(int64 Amount, FString Id, FOptionalInt64 UpdatedAt, FOptionalFederationInfo Proxy, FOptionalArrayOfCurrencyProperty Properties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break Currency", meta=(NativeBreakFunc))
	static void Break(const UCurrency* Serializable, int64& Amount, FString& Id, FOptionalInt64& UpdatedAt, FOptionalFederationInfo& Proxy, FOptionalArrayOfCurrencyProperty& Properties);
};