
#pragma once

#include "CoreMinimal.h"
#include "DatabaseMeasurements.h"

#include "DatabaseMeasurementsLibrary.generated.h"


UCLASS(BlueprintType)
class BEAMABLECORE_API UDatabaseMeasurementsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Serialize DatabaseMeasurements To JSON String")
	static FString DatabaseMeasurementsToJsonString(const UDatabaseMeasurements* Serializable, const bool Pretty);		
};