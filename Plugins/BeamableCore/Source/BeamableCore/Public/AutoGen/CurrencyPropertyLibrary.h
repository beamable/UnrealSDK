#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CurrencyProperty.h"

#include "CurrencyPropertyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCurrencyPropertyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - CurrencyProperty To JSON String")
	static FString CurrencyPropertyToJsonString(const UCurrencyProperty* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make CurrencyProperty", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UCurrencyProperty* Make(FString Name, FString Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break CurrencyProperty", meta=(NativeBreakFunc))
	static void Break(const UCurrencyProperty* Serializable, FString& Name, FString& Value);
};