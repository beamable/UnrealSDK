

#include "AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceComponentLibrary.h"

FOptionalArrayOfBeamoV2ServiceComponent UOptionalArrayOfBeamoV2ServiceComponentLibrary::MakeOptional(TArray<UBeamoV2ServiceComponent*> Value)
{
	FOptionalArrayOfBeamoV2ServiceComponent Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoV2ServiceComponent UOptionalArrayOfBeamoV2ServiceComponentLibrary::Conv_OptionalFromValue(TArray<UBeamoV2ServiceComponent*> Value)
{
	FOptionalArrayOfBeamoV2ServiceComponent Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoV2ServiceComponentLibrary::HasValue(const FOptionalArrayOfBeamoV2ServiceComponent& Optional, TArray<UBeamoV2ServiceComponent*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoV2ServiceComponent*> UOptionalArrayOfBeamoV2ServiceComponentLibrary::GetOptionalValue(const FOptionalArrayOfBeamoV2ServiceComponent& Optional, TArray<UBeamoV2ServiceComponent*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

