#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LocalizedPrice.h"

#include "LocalizedPriceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULocalizedPriceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Json", DisplayName="LocalizedPrice To JSON String")
	static FString LocalizedPriceToJsonString(const ULocalizedPrice* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make LocalizedPrice", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULocalizedPrice* Make(int64 To, int64 Price, double PriceLocalized, FString PriceLocalizedString, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Break LocalizedPrice", meta=(NativeBreakFunc))
	static void Break(const ULocalizedPrice* Serializable, int64& To, int64& Price, double& PriceLocalized, FString& PriceLocalizedString);
};