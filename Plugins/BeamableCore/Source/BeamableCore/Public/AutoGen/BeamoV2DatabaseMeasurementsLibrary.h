#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2DatabaseMeasurements.h"

#include "BeamoV2DatabaseMeasurementsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2DatabaseMeasurementsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2DatabaseMeasurements To JSON String")
	static FString BeamoV2DatabaseMeasurementsToJsonString(const UBeamoV2DatabaseMeasurements* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2DatabaseMeasurements", meta=(DefaultToSelf="Outer", AdvancedDisplay="Granularity, GroupId, HostId, ProcessId, Start, End, Links, Measurements, Outer", NativeMakeFunc))
	static UBeamoV2DatabaseMeasurements* Make(FString DatabaseName, FOptionalString Granularity, FOptionalString GroupId, FOptionalString HostId, FOptionalString ProcessId, FOptionalDateTime Start, FOptionalDateTime End, FOptionalArrayOfBeamoV2Link Links, FOptionalArrayOfBeamoV2DatabaseMeasurement Measurements, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2DatabaseMeasurements", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2DatabaseMeasurements* Serializable, FString& DatabaseName, FOptionalString& Granularity, FOptionalString& GroupId, FOptionalString& HostId, FOptionalString& ProcessId, FOptionalDateTime& Start, FOptionalDateTime& End, FOptionalArrayOfBeamoV2Link& Links, FOptionalArrayOfBeamoV2DatabaseMeasurement& Measurements);
};