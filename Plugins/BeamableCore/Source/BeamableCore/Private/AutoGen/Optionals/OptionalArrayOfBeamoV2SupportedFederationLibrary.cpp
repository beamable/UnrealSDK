

#include "AutoGen/Optionals/OptionalArrayOfBeamoV2SupportedFederationLibrary.h"

FOptionalArrayOfBeamoV2SupportedFederation UOptionalArrayOfBeamoV2SupportedFederationLibrary::MakeOptional(TArray<UBeamoV2SupportedFederation*> Value)
{
	FOptionalArrayOfBeamoV2SupportedFederation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamoV2SupportedFederation UOptionalArrayOfBeamoV2SupportedFederationLibrary::Conv_OptionalFromValue(TArray<UBeamoV2SupportedFederation*> Value)
{
	FOptionalArrayOfBeamoV2SupportedFederation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamoV2SupportedFederationLibrary::HasValue(const FOptionalArrayOfBeamoV2SupportedFederation& Optional, TArray<UBeamoV2SupportedFederation*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UBeamoV2SupportedFederation*> UOptionalArrayOfBeamoV2SupportedFederationLibrary::GetOptionalValue(const FOptionalArrayOfBeamoV2SupportedFederation& Optional, TArray<UBeamoV2SupportedFederation*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

