

#include "AutoGen/Optionals/OptionalEventPlayerGroupStateLibrary.h"

FOptionalEventPlayerGroupState UOptionalEventPlayerGroupStateLibrary::MakeOptional(UEventPlayerGroupState* Value)
{
	FOptionalEventPlayerGroupState Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalEventPlayerGroupState UOptionalEventPlayerGroupStateLibrary::Conv_OptionalFromValue(UEventPlayerGroupState* Value)
{
	FOptionalEventPlayerGroupState Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalEventPlayerGroupStateLibrary::HasValue(const FOptionalEventPlayerGroupState& Optional, UEventPlayerGroupState*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UEventPlayerGroupState* UOptionalEventPlayerGroupStateLibrary::GetOptionalValue(const FOptionalEventPlayerGroupState& Optional, UEventPlayerGroupState* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

