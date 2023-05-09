#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ProductView.h"

#include "ProductViewLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UProductViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ProductView To JSON String")
	static FString ProductViewToJsonString(const UProductView* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ProductView", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UProductView* Make(double LocalizedPrice, FString Sku, FString Description, FString IsoCurrencyCode, FString LocalizedPriceString, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ProductView", meta=(NativeBreakFunc))
	static void Break(const UProductView* Serializable, double& LocalizedPrice, FString& Sku, FString& Description, FString& IsoCurrencyCode, FString& LocalizedPriceString);
};