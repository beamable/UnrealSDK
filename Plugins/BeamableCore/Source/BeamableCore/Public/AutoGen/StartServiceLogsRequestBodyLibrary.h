#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StartServiceLogsRequestBody.h"

#include "StartServiceLogsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStartServiceLogsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="StartServiceLogsRequestBody To JSON String")
	static FString StartServiceLogsRequestBodyToJsonString(const UStartServiceLogsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make StartServiceLogsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="ServiceName, StartTime, EndTime, Order, Limit, Filters, Outer", NativeMakeFunc))
	static UStartServiceLogsRequestBody* Make(FOptionalString ServiceName, FOptionalDateTime StartTime, FOptionalDateTime EndTime, FOptionalOrderDirection Order, FOptionalInt32 Limit, FOptionalArrayOfString Filters, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break StartServiceLogsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UStartServiceLogsRequestBody* Serializable, FOptionalString& ServiceName, FOptionalDateTime& StartTime, FOptionalDateTime& EndTime, FOptionalOrderDirection& Order, FOptionalInt32& Limit, FOptionalArrayOfString& Filters);
};