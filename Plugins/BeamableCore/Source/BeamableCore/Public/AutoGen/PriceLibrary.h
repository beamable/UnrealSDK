#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Price.h"

#include "PriceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPriceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - Price To JSON String")
	static FString PriceToJsonString(const UPrice* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make Price", meta=(DefaultToSelf="Outer", AdvancedDisplay="Amount, Schedule, Outer", NativeMakeFunc))
	static UPrice* Make(FString Type, FString Symbol, FOptionalInt32 Amount, FOptionalArrayOfInt32 Schedule, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break Price", meta=(NativeBreakFunc))
	static void Break(const UPrice* Serializable, FString& Type, FString& Symbol, FOptionalInt32& Amount, FOptionalArrayOfInt32& Schedule);
};