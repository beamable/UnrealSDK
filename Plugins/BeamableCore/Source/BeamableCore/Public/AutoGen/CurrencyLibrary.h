#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Currency.h"

#include "CurrencyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCurrencyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Json", DisplayName="Currency To JSON String")
	static FString CurrencyToJsonString(const UCurrency* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Make Currency", meta=(DefaultToSelf="Outer", AdvancedDisplay="UpdatedAt, Proxy, Properties, Outer", NativeMakeFunc))
	static UCurrency* Make(int64 Amount, FString Id, FOptionalInt64 UpdatedAt, FOptionalFederationInfo Proxy, FOptionalArrayOfCurrencyProperty Properties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Make/Break", DisplayName="Break Currency", meta=(NativeBreakFunc))
	static void Break(const UCurrency* Serializable, int64& Amount, FString& Id, FOptionalInt64& UpdatedAt, FOptionalFederationInfo& Proxy, FOptionalArrayOfCurrencyProperty& Properties);
};