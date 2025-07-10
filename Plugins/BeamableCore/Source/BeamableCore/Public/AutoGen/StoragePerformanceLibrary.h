#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/StoragePerformance.h"

#include "StoragePerformanceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UStoragePerformanceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="StoragePerformance To JSON String")
	static FString StoragePerformanceToJsonString(const UStoragePerformance* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make StoragePerformance", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UStoragePerformance* Make(UDatabaseMeasurements* DatabaseMeasurements, TArray<UPANamespace*> Namespaces, TArray<UPASuggestedIndex*> Indexes, TArray<UPASlowQuery*> Queries, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break StoragePerformance", meta=(NativeBreakFunc))
	static void Break(const UStoragePerformance* Serializable, UDatabaseMeasurements*& DatabaseMeasurements, TArray<UPANamespace*>& Namespaces, TArray<UPASuggestedIndex*>& Indexes, TArray<UPASlowQuery*>& Queries);
};