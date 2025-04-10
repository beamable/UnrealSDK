#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetLogsInsightUrlRequestBody.h"

#include "GetLogsInsightUrlRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetLogsInsightUrlRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="GetLogsInsightUrlRequestBody To JSON String")
	static FString GetLogsInsightUrlRequestBodyToJsonString(const UGetLogsInsightUrlRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make GetLogsInsightUrlRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="StartTime, Filter, EndTime, Order, Limit, Filters, Outer", NativeMakeFunc))
	static UGetLogsInsightUrlRequestBody* Make(FString ServiceName, FOptionalInt64 StartTime, FOptionalString Filter, FOptionalInt64 EndTime, FOptionalString Order, FOptionalInt32 Limit, FOptionalArrayOfString Filters, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break GetLogsInsightUrlRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetLogsInsightUrlRequestBody* Serializable, FString& ServiceName, FOptionalInt64& StartTime, FOptionalString& Filter, FOptionalInt64& EndTime, FOptionalString& Order, FOptionalInt32& Limit, FOptionalArrayOfString& Filters);
};