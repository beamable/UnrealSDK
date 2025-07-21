

#include "AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceReferenceLibrary.h"

FOptionalArrayOfBeamoV2ServiceReference UOptionalArrayOfBeamoV2ServiceReferenceLibrary::MakeOptional(TArray<UBeamoV2ServiceReference*> Value)
{
	FOptionalArrayOfBeamoV2ServiceReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoV2ServiceReference UOptionalArrayOfBeamoV2ServiceReferenceLibrary::Conv_OptionalFromValue(TArray<UBeamoV2ServiceReference*> Value)
{
	FOptionalArrayOfBeamoV2ServiceReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoV2ServiceReferenceLibrary::HasValue(const FOptionalArrayOfBeamoV2ServiceReference& Optional, TArray<UBeamoV2ServiceReference*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoV2ServiceReference*> UOptionalArrayOfBeamoV2ServiceReferenceLibrary::GetOptionalValue(const FOptionalArrayOfBeamoV2ServiceReference& Optional, TArray<UBeamoV2ServiceReference*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

