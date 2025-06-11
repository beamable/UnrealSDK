#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Price.h"

#include "PriceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPriceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="Price To JSON String")
	static FString PriceToJsonString(const UPrice* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make Price", meta=(DefaultToSelf="Outer", AdvancedDisplay="Amount, Schedule, Outer", NativeMakeFunc))
	static UPrice* Make(FString Type, FString Symbol, FOptionalInt32 Amount, FOptionalArrayOfInt32 Schedule, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break Price", meta=(NativeBreakFunc))
	static void Break(const UPrice* Serializable, FString& Type, FString& Symbol, FOptionalInt32& Amount, FOptionalArrayOfInt32& Schedule);
};