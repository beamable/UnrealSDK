

#include "AutoGen/Optionals/OptionalLobbyRestrictionLibrary.h"

FOptionalLobbyRestriction UOptionalLobbyRestrictionLibrary::MakeOptional(ELobbyRestriction Value)
{
	FOptionalLobbyRestriction Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalLobbyRestriction UOptionalLobbyRestrictionLibrary::Conv_OptionalFromValue(ELobbyRestriction Value)
{
	FOptionalLobbyRestriction Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalLobbyRestrictionLibrary::HasValue(const FOptionalLobbyRestriction& Optional, ELobbyRestriction& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

ELobbyRestriction UOptionalLobbyRestrictionLibrary::GetOptionalValue(const FOptionalLobbyRestriction& Optional, ELobbyRestriction DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

