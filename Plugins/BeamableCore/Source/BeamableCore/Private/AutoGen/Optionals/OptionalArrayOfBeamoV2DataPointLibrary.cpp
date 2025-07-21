

#include "AutoGen/Optionals/OptionalArrayOfBeamoV2DataPointLibrary.h"

FOptionalArrayOfBeamoV2DataPoint UOptionalArrayOfBeamoV2DataPointLibrary::MakeOptional(TArray<UBeamoV2DataPoint*> Value)
{
	FOptionalArrayOfBeamoV2DataPoint Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoV2DataPoint UOptionalArrayOfBeamoV2DataPointLibrary::Conv_OptionalFromValue(TArray<UBeamoV2DataPoint*> Value)
{
	FOptionalArrayOfBeamoV2DataPoint Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoV2DataPointLibrary::HasValue(const FOptionalArrayOfBeamoV2DataPoint& Optional, TArray<UBeamoV2DataPoint*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoV2DataPoint*> UOptionalArrayOfBeamoV2DataPointLibrary::GetOptionalValue(const FOptionalArrayOfBeamoV2DataPoint& Optional, TArray<UBeamoV2DataPoint*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

