#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/CurrencyDelta.h"

#include "CurrencyDeltaLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCurrencyDeltaLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="CurrencyDelta To JSON String")
	static FString CurrencyDeltaToJsonString(const UCurrencyDelta* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make CurrencyDelta", meta=(DefaultToSelf="Outer", AdvancedDisplay="Properties, Outer", NativeMakeFunc))
	static UCurrencyDelta* Make(int64 Before, int64 After, FOptionalMapOfPropertyDelta Properties, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break CurrencyDelta", meta=(NativeBreakFunc))
	static void Break(const UCurrencyDelta* Serializable, int64& Before, int64& After, FOptionalMapOfPropertyDelta& Properties);
};