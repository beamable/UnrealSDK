

#include "OptionalEventPlayerGroupStateLibrary.h"

FOptionalEventPlayerGroupState UOptionalEventPlayerGroupStateLibrary::MakeOptionalEventPlayerGroupState(UEventPlayerGroupState* Value)
{
	FOptionalEventPlayerGroupState Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalEventPlayerGroupState UOptionalEventPlayerGroupStateLibrary::Conv_OptionalEventPlayerGroupStateFromValue(UEventPlayerGroupState* Value)
{
	FOptionalEventPlayerGroupState Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

