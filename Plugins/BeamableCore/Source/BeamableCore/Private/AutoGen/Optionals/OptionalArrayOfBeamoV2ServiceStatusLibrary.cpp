

#include "AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceStatusLibrary.h"

FOptionalArrayOfBeamoV2ServiceStatus UOptionalArrayOfBeamoV2ServiceStatusLibrary::MakeOptional(TArray<UBeamoV2ServiceStatus*> Value)
{
	FOptionalArrayOfBeamoV2ServiceStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoV2ServiceStatus UOptionalArrayOfBeamoV2ServiceStatusLibrary::Conv_OptionalFromValue(TArray<UBeamoV2ServiceStatus*> Value)
{
	FOptionalArrayOfBeamoV2ServiceStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoV2ServiceStatusLibrary::HasValue(const FOptionalArrayOfBeamoV2ServiceStatus& Optional, TArray<UBeamoV2ServiceStatus*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoV2ServiceStatus*> UOptionalArrayOfBeamoV2ServiceStatusLibrary::GetOptionalValue(const FOptionalArrayOfBeamoV2ServiceStatus& Optional, TArray<UBeamoV2ServiceStatus*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

