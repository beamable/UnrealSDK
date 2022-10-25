

#include "AutoGen/Optionals/OptionalBeamoLimitsLibrary.h"

FOptionalBeamoLimits UOptionalBeamoLimitsLibrary::MakeOptional(UBeamoLimits* Value)
{
	FOptionalBeamoLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamoLimits UOptionalBeamoLimitsLibrary::Conv_OptionalFromValue(UBeamoLimits* Value)
{
	FOptionalBeamoLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamoLimitsLibrary::HasValue(const FOptionalBeamoLimits& Optional, UBeamoLimits*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UBeamoLimits* UOptionalBeamoLimitsLibrary::GetOptionalValue(const FOptionalBeamoLimits& Optional, UBeamoLimits* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

