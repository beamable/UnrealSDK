#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DatabaseMeasurements.h"

#include "DatabaseMeasurementsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDatabaseMeasurementsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - DatabaseMeasurements To JSON String")
	static FString DatabaseMeasurementsToJsonString(const UDatabaseMeasurements* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make DatabaseMeasurements", meta=(DefaultToSelf="Outer", AdvancedDisplay="GroupId, HostId, Granularity, End, Start, ProcessId, Measurements, Outer", NativeMakeFunc))
	static UDatabaseMeasurements* Make(FString DatabaseName, TArray<ULink*> Links, FOptionalString GroupId, FOptionalString HostId, FOptionalString Granularity, FOptionalString End, FOptionalString Start, FOptionalString ProcessId, FOptionalArrayOfDatabaseMeasurement Measurements, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break DatabaseMeasurements", meta=(NativeBreakFunc))
	static void Break(const UDatabaseMeasurements* Serializable, FString& DatabaseName, TArray<ULink*>& Links, FOptionalString& GroupId, FOptionalString& HostId, FOptionalString& Granularity, FOptionalString& End, FOptionalString& Start, FOptionalString& ProcessId, FOptionalArrayOfDatabaseMeasurement& Measurements);
};