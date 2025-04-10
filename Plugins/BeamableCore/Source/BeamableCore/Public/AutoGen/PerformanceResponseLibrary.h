#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PerformanceResponse.h"

#include "PerformanceResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPerformanceResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="PerformanceResponse To JSON String")
	static FString PerformanceResponseToJsonString(const UPerformanceResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make PerformanceResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPerformanceResponse* Make(UDatabaseMeasurements* DatabaseMeasurements, TArray<UPANamespace*> Namespaces, TArray<UPASuggestedIndex*> Indexes, TArray<UPASlowQuery*> Queries, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break PerformanceResponse", meta=(NativeBreakFunc))
	static void Break(const UPerformanceResponse* Serializable, UDatabaseMeasurements*& DatabaseMeasurements, TArray<UPANamespace*>& Namespaces, TArray<UPASuggestedIndex*>& Indexes, TArray<UPASlowQuery*>& Queries);
};