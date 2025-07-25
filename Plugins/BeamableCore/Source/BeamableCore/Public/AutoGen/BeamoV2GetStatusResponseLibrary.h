#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2GetStatusResponse.h"

#include "BeamoV2GetStatusResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2GetStatusResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2GetStatusResponse To JSON String")
	static FString BeamoV2GetStatusResponseToJsonString(const UBeamoV2GetStatusResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2GetStatusResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="bIsCurrent, Services, StorageStatuses, Outer", NativeMakeFunc))
	static UBeamoV2GetStatusResponse* Make(FOptionalBool bIsCurrent, FOptionalArrayOfBeamoV2ServiceStatus Services, FOptionalArrayOfBeamoV2ServiceStorageStatus StorageStatuses, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2GetStatusResponse", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2GetStatusResponse* Serializable, FOptionalBool& bIsCurrent, FOptionalArrayOfBeamoV2ServiceStatus& Services, FOptionalArrayOfBeamoV2ServiceStorageStatus& StorageStatuses);
};