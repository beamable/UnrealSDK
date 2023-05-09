#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DatabasePerformanceRequestBody.h"

#include "DatabasePerformanceRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDatabasePerformanceRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - DatabasePerformanceRequestBody To JSON String")
	static FString DatabasePerformanceRequestBodyToJsonString(const UDatabasePerformanceRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make DatabasePerformanceRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="EndDate, StartDate, Period, Outer", NativeMakeFunc))
	static UDatabasePerformanceRequestBody* Make(FString StorageObjectName, FString Granularity, FOptionalString EndDate, FOptionalString StartDate, FOptionalString Period, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break DatabasePerformanceRequestBody", meta=(NativeBreakFunc))
	static void Break(const UDatabasePerformanceRequestBody* Serializable, FString& StorageObjectName, FString& Granularity, FOptionalString& EndDate, FOptionalString& StartDate, FOptionalString& Period);
};