

#include "AutoGen/Optionals/OptionalArrayOfBeamoV2DatabaseMeasurementLibrary.h"

FOptionalArrayOfBeamoV2DatabaseMeasurement UOptionalArrayOfBeamoV2DatabaseMeasurementLibrary::MakeOptional(TArray<UBeamoV2DatabaseMeasurement*> Value)
{
	FOptionalArrayOfBeamoV2DatabaseMeasurement Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoV2DatabaseMeasurement UOptionalArrayOfBeamoV2DatabaseMeasurementLibrary::Conv_OptionalFromValue(TArray<UBeamoV2DatabaseMeasurement*> Value)
{
	FOptionalArrayOfBeamoV2DatabaseMeasurement Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoV2DatabaseMeasurementLibrary::HasValue(const FOptionalArrayOfBeamoV2DatabaseMeasurement& Optional, TArray<UBeamoV2DatabaseMeasurement*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoV2DatabaseMeasurement*> UOptionalArrayOfBeamoV2DatabaseMeasurementLibrary::GetOptionalValue(const FOptionalArrayOfBeamoV2DatabaseMeasurement& Optional, TArray<UBeamoV2DatabaseMeasurement*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

