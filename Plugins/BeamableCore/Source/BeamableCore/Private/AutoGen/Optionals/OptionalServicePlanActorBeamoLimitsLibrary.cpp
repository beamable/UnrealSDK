

#include "AutoGen/Optionals/OptionalServicePlanActorBeamoLimitsLibrary.h"

FOptionalServicePlanActorBeamoLimits UOptionalServicePlanActorBeamoLimitsLibrary::MakeOptional(UServicePlanActorBeamoLimits* Value)
{
	FOptionalServicePlanActorBeamoLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalServicePlanActorBeamoLimits UOptionalServicePlanActorBeamoLimitsLibrary::Conv_OptionalFromValue(UServicePlanActorBeamoLimits* Value)
{
	FOptionalServicePlanActorBeamoLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalServicePlanActorBeamoLimitsLibrary::HasValue(const FOptionalServicePlanActorBeamoLimits& Optional, UServicePlanActorBeamoLimits*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UServicePlanActorBeamoLimits* UOptionalServicePlanActorBeamoLimitsLibrary::GetOptionalValue(const FOptionalServicePlanActorBeamoLimits& Optional, UServicePlanActorBeamoLimits* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

