

#include "AutoGen/Optionals/OptionalRealmsBasicBeamoLimitsLibrary.h"

FOptionalRealmsBasicBeamoLimits UOptionalRealmsBasicBeamoLimitsLibrary::MakeOptional(URealmsBasicBeamoLimits* Value)
{
	FOptionalRealmsBasicBeamoLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalRealmsBasicBeamoLimits UOptionalRealmsBasicBeamoLimitsLibrary::Conv_OptionalFromValue(URealmsBasicBeamoLimits* Value)
{
	FOptionalRealmsBasicBeamoLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalRealmsBasicBeamoLimitsLibrary::HasValue(const FOptionalRealmsBasicBeamoLimits& Optional, URealmsBasicBeamoLimits*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

URealmsBasicBeamoLimits* UOptionalRealmsBasicBeamoLimitsLibrary::GetOptionalValue(const FOptionalRealmsBasicBeamoLimits& Optional, URealmsBasicBeamoLimits* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

