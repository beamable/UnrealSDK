

#include "AutoGen/Optionals/OptionalPresenceStatusLibrary.h"

FOptionalPresenceStatus UOptionalPresenceStatusLibrary::MakeOptional(EPresenceStatus Value)
{
	FOptionalPresenceStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalPresenceStatus UOptionalPresenceStatusLibrary::Conv_OptionalFromValue(EPresenceStatus Value)
{
	FOptionalPresenceStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalPresenceStatusLibrary::HasValue(const FOptionalPresenceStatus& Optional, EPresenceStatus& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

EPresenceStatus UOptionalPresenceStatusLibrary::GetOptionalValue(const FOptionalPresenceStatus& Optional, EPresenceStatus DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

