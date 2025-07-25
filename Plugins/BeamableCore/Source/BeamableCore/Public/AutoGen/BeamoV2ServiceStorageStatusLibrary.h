#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceStorageStatus.h"

#include "BeamoV2ServiceStorageStatusLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ServiceStorageStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2ServiceStorageStatus To JSON String")
	static FString BeamoV2ServiceStorageStatusToJsonString(const UBeamoV2ServiceStorageStatus* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2ServiceStorageStatus", meta=(DefaultToSelf="Outer", AdvancedDisplay="bIsCurrent, bIsRunning, Id, StorageType, Outer", NativeMakeFunc))
	static UBeamoV2ServiceStorageStatus* Make(FOptionalBool bIsCurrent, FOptionalBool bIsRunning, FOptionalString Id, FOptionalString StorageType, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2ServiceStorageStatus", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2ServiceStorageStatus* Serializable, FOptionalBool& bIsCurrent, FOptionalBool& bIsRunning, FOptionalString& Id, FOptionalString& StorageType);
};