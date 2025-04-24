#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetLogsUrlRequestBody.h"

#include "GetLogsUrlRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetLogsUrlRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="GetLogsUrlRequestBody To JSON String")
	static FString GetLogsUrlRequestBodyToJsonString(const UGetLogsUrlRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make GetLogsUrlRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="StartTime, NextToken, Filter, EndTime, Limit, Outer", NativeMakeFunc))
	static UGetLogsUrlRequestBody* Make(FString ServiceName, FOptionalInt64 StartTime, FOptionalString NextToken, FOptionalString Filter, FOptionalInt64 EndTime, FOptionalInt32 Limit, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break GetLogsUrlRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetLogsUrlRequestBody* Serializable, FString& ServiceName, FOptionalInt64& StartTime, FOptionalString& NextToken, FOptionalString& Filter, FOptionalInt64& EndTime, FOptionalInt32& Limit);
};