

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalArrayOfDatabaseMeasurement.h"

#include "OptionalArrayOfDatabaseMeasurementLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfDatabaseMeasurementLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam Optional Makes")
	static FOptionalArrayOfDatabaseMeasurement MakeOptionalArrayOfDatabaseMeasurement(TArray<UDatabaseMeasurement*> Value);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "TArray<UDatabaseMeasurement*> To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam Optional Converters")
	static FOptionalArrayOfDatabaseMeasurement Conv_OptionalArrayOfDatabaseMeasurementFromValue(TArray<UDatabaseMeasurement*> Value);
};
