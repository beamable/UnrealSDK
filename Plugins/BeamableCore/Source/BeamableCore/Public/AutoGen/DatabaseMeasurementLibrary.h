#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/DatabaseMeasurement.h"

#include "DatabaseMeasurementLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UDatabaseMeasurementLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - DatabaseMeasurement To JSON String")
	static FString DatabaseMeasurementToJsonString(const UDatabaseMeasurement* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make DatabaseMeasurement", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UDatabaseMeasurement* Make(FString Name, FString Units, TArray<UDataPoint*> DataPoints, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break DatabaseMeasurement", meta=(NativeBreakFunc))
	static void Break(const UDatabaseMeasurement* Serializable, FString& Name, FString& Units, TArray<UDataPoint*>& DataPoints);
};