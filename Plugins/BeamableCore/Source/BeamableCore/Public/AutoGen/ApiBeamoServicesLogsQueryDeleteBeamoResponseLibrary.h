#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ApiBeamoServicesLogsQueryDeleteBeamoResponse.h"

#include "ApiBeamoServicesLogsQueryDeleteBeamoResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UApiBeamoServicesLogsQueryDeleteBeamoResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="ApiBeamoServicesLogsQueryDeleteBeamoResponse To JSON String")
	static FString ApiBeamoServicesLogsQueryDeleteBeamoResponseToJsonString(const UApiBeamoServicesLogsQueryDeleteBeamoResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make ApiBeamoServicesLogsQueryDeleteBeamoResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UApiBeamoServicesLogsQueryDeleteBeamoResponse* Make(UObject* Outer);

	
};