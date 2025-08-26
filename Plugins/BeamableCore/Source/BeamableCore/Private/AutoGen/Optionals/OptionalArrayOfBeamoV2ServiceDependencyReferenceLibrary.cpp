

#include "AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceDependencyReferenceLibrary.h"

FOptionalArrayOfBeamoV2ServiceDependencyReference UOptionalArrayOfBeamoV2ServiceDependencyReferenceLibrary::MakeOptional(TArray<UBeamoV2ServiceDependencyReference*> Value)
{
	FOptionalArrayOfBeamoV2ServiceDependencyReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoV2ServiceDependencyReference UOptionalArrayOfBeamoV2ServiceDependencyReferenceLibrary::Conv_OptionalFromValue(TArray<UBeamoV2ServiceDependencyReference*> Value)
{
	FOptionalArrayOfBeamoV2ServiceDependencyReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoV2ServiceDependencyReferenceLibrary::HasValue(const FOptionalArrayOfBeamoV2ServiceDependencyReference& Optional, TArray<UBeamoV2ServiceDependencyReference*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoV2ServiceDependencyReference*> UOptionalArrayOfBeamoV2ServiceDependencyReferenceLibrary::GetOptionalValue(const FOptionalArrayOfBeamoV2ServiceDependencyReference& Optional, TArray<UBeamoV2ServiceDependencyReference*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

