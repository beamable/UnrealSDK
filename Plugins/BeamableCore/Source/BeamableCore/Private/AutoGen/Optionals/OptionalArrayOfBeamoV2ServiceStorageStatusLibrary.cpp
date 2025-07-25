

#include "AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceStorageStatusLibrary.h"

FOptionalArrayOfBeamoV2ServiceStorageStatus UOptionalArrayOfBeamoV2ServiceStorageStatusLibrary::MakeOptional(TArray<UBeamoV2ServiceStorageStatus*> Value)
{
	FOptionalArrayOfBeamoV2ServiceStorageStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoV2ServiceStorageStatus UOptionalArrayOfBeamoV2ServiceStorageStatusLibrary::Conv_OptionalFromValue(TArray<UBeamoV2ServiceStorageStatus*> Value)
{
	FOptionalArrayOfBeamoV2ServiceStorageStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoV2ServiceStorageStatusLibrary::HasValue(const FOptionalArrayOfBeamoV2ServiceStorageStatus& Optional, TArray<UBeamoV2ServiceStorageStatus*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoV2ServiceStorageStatus*> UOptionalArrayOfBeamoV2ServiceStorageStatusLibrary::GetOptionalValue(const FOptionalArrayOfBeamoV2ServiceStorageStatus& Optional, TArray<UBeamoV2ServiceStorageStatus*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

