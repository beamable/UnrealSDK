#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/LocalizedPriceMap.h"

#include "LocalizedPriceMapLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API ULocalizedPriceMapLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Json", DisplayName="LocalizedPriceMap To JSON String")
	static FString LocalizedPriceMapToJsonString(const ULocalizedPriceMap* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Make LocalizedPriceMap", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static ULocalizedPriceMap* Make(FString Currency, TArray<ULocalizedPrice*> Prices, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Payments|Utils|Make/Break", DisplayName="Break LocalizedPriceMap", meta=(NativeBreakFunc))
	static void Break(const ULocalizedPriceMap* Serializable, FString& Currency, TArray<ULocalizedPrice*>& Prices);
};