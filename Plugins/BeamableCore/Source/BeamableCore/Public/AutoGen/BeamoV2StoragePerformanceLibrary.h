#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2StoragePerformance.h"

#include "BeamoV2StoragePerformanceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2StoragePerformanceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2StoragePerformance To JSON String")
	static FString BeamoV2StoragePerformanceToJsonString(const UBeamoV2StoragePerformance* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2StoragePerformance", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBeamoV2StoragePerformance* Make(UBeamoV2DatabaseMeasurements* DatabaseMeasurements, TArray<UBeamoV2PANamespace*> Namespaces, TArray<UBeamoV2PASuggestedIndex*> Indexes, TArray<UBeamoV2PASlowQuery*> Queries, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2StoragePerformance", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2StoragePerformance* Serializable, UBeamoV2DatabaseMeasurements*& DatabaseMeasurements, TArray<UBeamoV2PANamespace*>& Namespaces, TArray<UBeamoV2PASuggestedIndex*>& Indexes, TArray<UBeamoV2PASlowQuery*>& Queries);
};