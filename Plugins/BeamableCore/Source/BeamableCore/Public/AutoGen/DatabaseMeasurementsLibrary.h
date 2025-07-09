#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DatabaseMeasurements.h"

#include "DatabaseMeasurementsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDatabaseMeasurementsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="DatabaseMeasurements To JSON String")
	static FString DatabaseMeasurementsToJsonString(const UDatabaseMeasurements* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make DatabaseMeasurements", meta=(DefaultToSelf="Outer", AdvancedDisplay="Granularity, GroupId, HostId, ProcessId, Start, End, Links, Measurements, Outer", NativeMakeFunc))
	static UDatabaseMeasurements* Make(FString DatabaseName, FOptionalString Granularity, FOptionalString GroupId, FOptionalString HostId, FOptionalString ProcessId, FOptionalDateTime Start, FOptionalDateTime End, FOptionalArrayOfLink Links, FOptionalArrayOfDatabaseMeasurement Measurements, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break DatabaseMeasurements", meta=(NativeBreakFunc))
	static void Break(const UDatabaseMeasurements* Serializable, FString& DatabaseName, FOptionalString& Granularity, FOptionalString& GroupId, FOptionalString& HostId, FOptionalString& ProcessId, FOptionalDateTime& Start, FOptionalDateTime& End, FOptionalArrayOfLink& Links, FOptionalArrayOfDatabaseMeasurement& Measurements);
};