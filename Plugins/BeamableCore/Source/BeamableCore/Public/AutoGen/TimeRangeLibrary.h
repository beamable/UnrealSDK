#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/TimeRange.h"

#include "TimeRangeLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UTimeRangeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Json", DisplayName="TimeRange To JSON String")
	static FString TimeRangeToJsonString(const UTimeRange* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Make TimeRange", meta=(DefaultToSelf="Outer", AdvancedDisplay="From, To, Outer", NativeMakeFunc))
	static UTimeRange* Make(FOptionalInt64 From, FOptionalInt64 To, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Make/Break", DisplayName="Break TimeRange", meta=(NativeBreakFunc))
	static void Break(const UTimeRange* Serializable, FOptionalInt64& From, FOptionalInt64& To);
};