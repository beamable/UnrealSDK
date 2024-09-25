#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/EventsWithinDateRangeRequestBody.h"

#include "EventsWithinDateRangeRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventsWithinDateRangeRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - EventsWithinDateRangeRequestBody To JSON String")
	static FString EventsWithinDateRangeRequestBodyToJsonString(const UEventsWithinDateRangeRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make EventsWithinDateRangeRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="From, To, Query, Limit, Outer", NativeMakeFunc))
	static UEventsWithinDateRangeRequestBody* Make(FOptionalString From, FOptionalString To, FOptionalString Query, FOptionalInt32 Limit, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break EventsWithinDateRangeRequestBody", meta=(NativeBreakFunc))
	static void Break(const UEventsWithinDateRangeRequestBody* Serializable, FOptionalString& From, FOptionalString& To, FOptionalString& Query, FOptionalInt32& Limit);
};