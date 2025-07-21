#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse.h"

#include "BeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse To JSON String")
	static FString BeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponseToJsonString(const UBeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBeamoV2ApiBeamoServicesLogsQueryDeleteBeamoResponse* Make(UObject* Outer);

	
};