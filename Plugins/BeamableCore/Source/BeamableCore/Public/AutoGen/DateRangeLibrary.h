#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DateRange.h"

#include "DateRangeLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDateRangeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="DateRange To JSON String")
	static FString DateRangeToJsonString(const UDateRange* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make DateRange", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDateRange* Make(FString From, FString To, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break DateRange", meta=(NativeBreakFunc))
	static void Break(const UDateRange* Serializable, FString& From, FString& To);
};