#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/LocalizedPrice.h"

#include "LocalizedPriceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULocalizedPriceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - LocalizedPrice To JSON String")
	static FString LocalizedPriceToJsonString(const ULocalizedPrice* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make LocalizedPrice", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULocalizedPrice* Make(int64 To, int64 Price, double PriceLocalized, FString PriceLocalizedString, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break LocalizedPrice", meta=(NativeBreakFunc))
	static void Break(const ULocalizedPrice* Serializable, int64& To, int64& Price, double& PriceLocalized, FString& PriceLocalizedString);
};