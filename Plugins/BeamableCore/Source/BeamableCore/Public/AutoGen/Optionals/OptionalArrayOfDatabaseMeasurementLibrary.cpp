

#include "OptionalArrayOfDatabaseMeasurementLibrary.h"

FOptionalArrayOfDatabaseMeasurement UOptionalArrayOfDatabaseMeasurementLibrary::MakeOptionalArrayOfDatabaseMeasurement(TArray<UDatabaseMeasurement*> Value)
{
	FOptionalArrayOfDatabaseMeasurement Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfDatabaseMeasurement UOptionalArrayOfDatabaseMeasurementLibrary::Conv_OptionalArrayOfDatabaseMeasurementFromValue(TArray<UDatabaseMeasurement*> Value)
{
	FOptionalArrayOfDatabaseMeasurement Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

