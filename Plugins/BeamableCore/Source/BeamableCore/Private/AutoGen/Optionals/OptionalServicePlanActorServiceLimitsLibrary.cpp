

#include "AutoGen/Optionals/OptionalServicePlanActorServiceLimitsLibrary.h"

FOptionalServicePlanActorServiceLimits UOptionalServicePlanActorServiceLimitsLibrary::MakeOptional(UServicePlanActorServiceLimits* Value)
{
	FOptionalServicePlanActorServiceLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalServicePlanActorServiceLimits UOptionalServicePlanActorServiceLimitsLibrary::Conv_OptionalFromValue(UServicePlanActorServiceLimits* Value)
{
	FOptionalServicePlanActorServiceLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalServicePlanActorServiceLimitsLibrary::HasValue(const FOptionalServicePlanActorServiceLimits& Optional, UServicePlanActorServiceLimits*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UServicePlanActorServiceLimits* UOptionalServicePlanActorServiceLimitsLibrary::GetOptionalValue(const FOptionalServicePlanActorServiceLimits& Optional, UServicePlanActorServiceLimits* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

