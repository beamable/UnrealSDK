

#include "AutoGen/Optionals/OptionalLobbyRestrictionLibrary.h"

FOptionalLobbyRestriction UOptionalLobbyRestrictionLibrary::MakeOptional(EBeamLobbyRestriction Value)
{
	FOptionalLobbyRestriction Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalLobbyRestriction UOptionalLobbyRestrictionLibrary::Conv_OptionalFromValue(EBeamLobbyRestriction Value)
{
	FOptionalLobbyRestriction Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalLobbyRestrictionLibrary::HasValue(const FOptionalLobbyRestriction& Optional, EBeamLobbyRestriction& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

EBeamLobbyRestriction UOptionalLobbyRestrictionLibrary::GetOptionalValue(const FOptionalLobbyRestriction& Optional, EBeamLobbyRestriction DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

