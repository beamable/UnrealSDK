

#include "OptionalScheduleLibrary.h"

FOptionalSchedule UOptionalScheduleLibrary::MakeOptionalSchedule(USchedule* Value)
{
	FOptionalSchedule Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalSchedule UOptionalScheduleLibrary::Conv_OptionalScheduleFromValue(USchedule* Value)
{
	FOptionalSchedule Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

