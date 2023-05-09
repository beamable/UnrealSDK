#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DateRange.h"

#include "DateRangeLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDateRangeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - DateRange To JSON String")
	static FString DateRangeToJsonString(const UDateRange* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make DateRange", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDateRange* Make(FString From, FString To, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break DateRange", meta=(NativeBreakFunc))
	static void Break(const UDateRange* Serializable, FString& From, FString& To);
};