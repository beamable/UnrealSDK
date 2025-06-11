

#include "AutoGen/Optionals/OptionalPresenceStatusLibrary.h"

FOptionalPresenceStatus UOptionalPresenceStatusLibrary::MakeOptional(EBeamPresenceStatus Value)
{
	FOptionalPresenceStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalPresenceStatus UOptionalPresenceStatusLibrary::Conv_OptionalFromValue(EBeamPresenceStatus Value)
{
	FOptionalPresenceStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalPresenceStatusLibrary::HasValue(const FOptionalPresenceStatus& Optional, EBeamPresenceStatus& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

EBeamPresenceStatus UOptionalPresenceStatusLibrary::GetOptionalValue(const FOptionalPresenceStatus& Optional, EBeamPresenceStatus DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

