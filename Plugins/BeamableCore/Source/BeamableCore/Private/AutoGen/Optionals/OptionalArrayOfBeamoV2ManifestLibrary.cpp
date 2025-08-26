

#include "AutoGen/Optionals/OptionalArrayOfBeamoV2ManifestLibrary.h"

FOptionalArrayOfBeamoV2Manifest UOptionalArrayOfBeamoV2ManifestLibrary::MakeOptional(TArray<UBeamoV2Manifest*> Value)
{
	FOptionalArrayOfBeamoV2Manifest Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoV2Manifest UOptionalArrayOfBeamoV2ManifestLibrary::Conv_OptionalFromValue(TArray<UBeamoV2Manifest*> Value)
{
	FOptionalArrayOfBeamoV2Manifest Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoV2ManifestLibrary::HasValue(const FOptionalArrayOfBeamoV2Manifest& Optional, TArray<UBeamoV2Manifest*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoV2Manifest*> UOptionalArrayOfBeamoV2ManifestLibrary::GetOptionalValue(const FOptionalArrayOfBeamoV2Manifest& Optional, TArray<UBeamoV2Manifest*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

