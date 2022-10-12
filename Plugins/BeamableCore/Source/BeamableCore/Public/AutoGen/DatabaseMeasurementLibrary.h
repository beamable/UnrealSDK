
#pragma once

#include "CoreMinimal.h"
#include "DatabaseMeasurement.h"

#include "DatabaseMeasurementLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UDatabaseMeasurementLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize DatabaseMeasurement To JSON String")
	static FString DatabaseMeasurementToJsonString(const UDatabaseMeasurement* Serializable, const bool Pretty);		
};