#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceStatus.h"

#include "BeamoV2ServiceStatusLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ServiceStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2ServiceStatus To JSON String")
	static FString BeamoV2ServiceStatusToJsonString(const UBeamoV2ServiceStatus* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2ServiceStatus", meta=(DefaultToSelf="Outer", AdvancedDisplay="bIsCurrent, bRunning, ServiceName, ImageId, ServiceDependencyReferences, Outer", NativeMakeFunc))
	static UBeamoV2ServiceStatus* Make(FOptionalBool bIsCurrent, FOptionalBool bRunning, FOptionalString ServiceName, FOptionalString ImageId, FOptionalArrayOfBeamoV2ServiceDependencyReference ServiceDependencyReferences, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2ServiceStatus", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2ServiceStatus* Serializable, FOptionalBool& bIsCurrent, FOptionalBool& bRunning, FOptionalString& ServiceName, FOptionalString& ImageId, FOptionalArrayOfBeamoV2ServiceDependencyReference& ServiceDependencyReferences);
};