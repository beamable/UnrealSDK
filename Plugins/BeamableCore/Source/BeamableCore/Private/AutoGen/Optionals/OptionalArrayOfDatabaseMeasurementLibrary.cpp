

#include "AutoGen/Optionals/OptionalArrayOfDatabaseMeasurementLibrary.h"

FOptionalArrayOfDatabaseMeasurement UOptionalArrayOfDatabaseMeasurementLibrary::MakeOptional(TArray<UDatabaseMeasurement*> Value)
{
	FOptionalArrayOfDatabaseMeasurement Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfDatabaseMeasurement UOptionalArrayOfDatabaseMeasurementLibrary::Conv_OptionalFromValue(TArray<UDatabaseMeasurement*> Value)
{
	FOptionalArrayOfDatabaseMeasurement Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfDatabaseMeasurementLibrary::HasValue(const FOptionalArrayOfDatabaseMeasurement& Optional, TArray<UDatabaseMeasurement*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UDatabaseMeasurement*> UOptionalArrayOfDatabaseMeasurementLibrary::GetOptionalValue(const FOptionalArrayOfDatabaseMeasurement& Optional, TArray<UDatabaseMeasurement*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

