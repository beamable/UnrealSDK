

#include "AutoGen/Optionals/OptionalScheduleLibrary.h"

FOptionalSchedule UOptionalScheduleLibrary::MakeOptional(USchedule* Value)
{
	FOptionalSchedule Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalSchedule UOptionalScheduleLibrary::Conv_OptionalFromValue(USchedule* Value)
{
	FOptionalSchedule Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalScheduleLibrary::HasValue(const FOptionalSchedule& Optional, USchedule*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

USchedule* UOptionalScheduleLibrary::GetOptionalValue(const FOptionalSchedule& Optional, USchedule* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

