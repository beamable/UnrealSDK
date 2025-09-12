

#include "AutoGen/Optionals/OptionalBeamoV2LogProviderLibrary.h"

FOptionalBeamoV2LogProvider UOptionalBeamoV2LogProviderLibrary::MakeOptional(EBeamBeamoV2LogProvider Value)
{
	FOptionalBeamoV2LogProvider Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamoV2LogProvider UOptionalBeamoV2LogProviderLibrary::Conv_OptionalFromValue(EBeamBeamoV2LogProvider Value)
{
	FOptionalBeamoV2LogProvider Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamoV2LogProviderLibrary::HasValue(const FOptionalBeamoV2LogProvider& Optional, EBeamBeamoV2LogProvider& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

EBeamBeamoV2LogProvider UOptionalBeamoV2LogProviderLibrary::GetOptionalValue(const FOptionalBeamoV2LogProvider& Optional, EBeamBeamoV2LogProvider DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

