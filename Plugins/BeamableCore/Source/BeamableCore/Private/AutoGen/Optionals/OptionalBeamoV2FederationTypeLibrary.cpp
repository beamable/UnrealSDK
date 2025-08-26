

#include "AutoGen/Optionals/OptionalBeamoV2FederationTypeLibrary.h"

FOptionalBeamoV2FederationType UOptionalBeamoV2FederationTypeLibrary::MakeOptional(EBeamBeamoV2FederationType Value)
{
	FOptionalBeamoV2FederationType Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamoV2FederationType UOptionalBeamoV2FederationTypeLibrary::Conv_OptionalFromValue(EBeamBeamoV2FederationType Value)
{
	FOptionalBeamoV2FederationType Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamoV2FederationTypeLibrary::HasValue(const FOptionalBeamoV2FederationType& Optional, EBeamBeamoV2FederationType& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

EBeamBeamoV2FederationType UOptionalBeamoV2FederationTypeLibrary::GetOptionalValue(const FOptionalBeamoV2FederationType& Optional, EBeamBeamoV2FederationType DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

