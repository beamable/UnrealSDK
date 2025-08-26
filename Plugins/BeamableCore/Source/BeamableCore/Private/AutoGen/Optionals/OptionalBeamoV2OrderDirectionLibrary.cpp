

#include "AutoGen/Optionals/OptionalBeamoV2OrderDirectionLibrary.h"

FOptionalBeamoV2OrderDirection UOptionalBeamoV2OrderDirectionLibrary::MakeOptional(EBeamBeamoV2OrderDirection Value)
{
	FOptionalBeamoV2OrderDirection Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamoV2OrderDirection UOptionalBeamoV2OrderDirectionLibrary::Conv_OptionalFromValue(EBeamBeamoV2OrderDirection Value)
{
	FOptionalBeamoV2OrderDirection Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamoV2OrderDirectionLibrary::HasValue(const FOptionalBeamoV2OrderDirection& Optional, EBeamBeamoV2OrderDirection& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

EBeamBeamoV2OrderDirection UOptionalBeamoV2OrderDirectionLibrary::GetOptionalValue(const FOptionalBeamoV2OrderDirection& Optional, EBeamBeamoV2OrderDirection DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

