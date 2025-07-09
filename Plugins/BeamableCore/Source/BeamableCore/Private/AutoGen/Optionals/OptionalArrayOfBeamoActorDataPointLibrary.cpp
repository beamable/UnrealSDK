

#include "AutoGen/Optionals/OptionalArrayOfBeamoActorDataPointLibrary.h"

FOptionalArrayOfBeamoActorDataPoint UOptionalArrayOfBeamoActorDataPointLibrary::MakeOptional(TArray<UBeamoActorDataPoint*> Value)
{
	FOptionalArrayOfBeamoActorDataPoint Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoActorDataPoint UOptionalArrayOfBeamoActorDataPointLibrary::Conv_OptionalFromValue(TArray<UBeamoActorDataPoint*> Value)
{
	FOptionalArrayOfBeamoActorDataPoint Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoActorDataPointLibrary::HasValue(const FOptionalArrayOfBeamoActorDataPoint& Optional, TArray<UBeamoActorDataPoint*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoActorDataPoint*> UOptionalArrayOfBeamoActorDataPointLibrary::GetOptionalValue(const FOptionalArrayOfBeamoActorDataPoint& Optional, TArray<UBeamoActorDataPoint*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

