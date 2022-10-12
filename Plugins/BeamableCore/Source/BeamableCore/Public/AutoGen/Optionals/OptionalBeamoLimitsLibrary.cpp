

#include "OptionalBeamoLimitsLibrary.h"

FOptionalBeamoLimits UOptionalBeamoLimitsLibrary::MakeOptionalBeamoLimits(UBeamoLimits* Value)
{
	FOptionalBeamoLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamoLimits UOptionalBeamoLimitsLibrary::Conv_OptionalBeamoLimitsFromValue(UBeamoLimits* Value)
{
	FOptionalBeamoLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

