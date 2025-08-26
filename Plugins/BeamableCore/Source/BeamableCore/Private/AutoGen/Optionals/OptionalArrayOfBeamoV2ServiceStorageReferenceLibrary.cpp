

#include "AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceStorageReferenceLibrary.h"

FOptionalArrayOfBeamoV2ServiceStorageReference UOptionalArrayOfBeamoV2ServiceStorageReferenceLibrary::MakeOptional(TArray<UBeamoV2ServiceStorageReference*> Value)
{
	FOptionalArrayOfBeamoV2ServiceStorageReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoV2ServiceStorageReference UOptionalArrayOfBeamoV2ServiceStorageReferenceLibrary::Conv_OptionalFromValue(TArray<UBeamoV2ServiceStorageReference*> Value)
{
	FOptionalArrayOfBeamoV2ServiceStorageReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoV2ServiceStorageReferenceLibrary::HasValue(const FOptionalArrayOfBeamoV2ServiceStorageReference& Optional, TArray<UBeamoV2ServiceStorageReference*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoV2ServiceStorageReference*> UOptionalArrayOfBeamoV2ServiceStorageReferenceLibrary::GetOptionalValue(const FOptionalArrayOfBeamoV2ServiceStorageReference& Optional, TArray<UBeamoV2ServiceStorageReference*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

