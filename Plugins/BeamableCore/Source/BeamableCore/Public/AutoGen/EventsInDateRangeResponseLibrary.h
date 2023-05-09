#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/EventsInDateRangeResponse.h"

#include "EventsInDateRangeResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventsInDateRangeResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - EventsInDateRangeResponse To JSON String")
	static FString EventsInDateRangeResponseToJsonString(const UEventsInDateRangeResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make EventsInDateRangeResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UEventsInDateRangeResponse* Make(TArray<UEventDateRanges*> EventInDateRange, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break EventsInDateRangeResponse", meta=(NativeBreakFunc))
	static void Break(const UEventsInDateRangeResponse* Serializable, TArray<UEventDateRanges*>& EventInDateRange);
};