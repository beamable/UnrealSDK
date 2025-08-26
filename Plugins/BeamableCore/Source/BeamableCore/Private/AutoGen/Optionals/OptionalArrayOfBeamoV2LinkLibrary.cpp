

#include "AutoGen/Optionals/OptionalArrayOfBeamoV2LinkLibrary.h"

FOptionalArrayOfBeamoV2Link UOptionalArrayOfBeamoV2LinkLibrary::MakeOptional(TArray<UBeamoV2Link*> Value)
{
	FOptionalArrayOfBeamoV2Link Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoV2Link UOptionalArrayOfBeamoV2LinkLibrary::Conv_OptionalFromValue(TArray<UBeamoV2Link*> Value)
{
	FOptionalArrayOfBeamoV2Link Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoV2LinkLibrary::HasValue(const FOptionalArrayOfBeamoV2Link& Optional, TArray<UBeamoV2Link*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoV2Link*> UOptionalArrayOfBeamoV2LinkLibrary::GetOptionalValue(const FOptionalArrayOfBeamoV2Link& Optional, TArray<UBeamoV2Link*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

