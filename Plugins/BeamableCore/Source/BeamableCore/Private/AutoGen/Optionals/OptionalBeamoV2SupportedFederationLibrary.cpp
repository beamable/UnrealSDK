

#include "AutoGen/Optionals/OptionalBeamoV2SupportedFederationLibrary.h"

FOptionalBeamoV2SupportedFederation UOptionalBeamoV2SupportedFederationLibrary::MakeOptional(UBeamoV2SupportedFederation* Value)
{
	FOptionalBeamoV2SupportedFederation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamoV2SupportedFederation UOptionalBeamoV2SupportedFederationLibrary::Conv_OptionalFromValue(UBeamoV2SupportedFederation* Value)
{
	FOptionalBeamoV2SupportedFederation Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamoV2SupportedFederationLibrary::HasValue(const FOptionalBeamoV2SupportedFederation& Optional, UBeamoV2SupportedFederation*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UBeamoV2SupportedFederation* UOptionalBeamoV2SupportedFederationLibrary::GetOptionalValue(const FOptionalBeamoV2SupportedFederation& Optional, UBeamoV2SupportedFederation* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

