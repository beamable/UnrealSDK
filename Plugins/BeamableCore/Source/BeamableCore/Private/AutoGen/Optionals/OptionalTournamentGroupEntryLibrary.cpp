

#include "AutoGen/Optionals/OptionalTournamentGroupEntryLibrary.h"

FOptionalTournamentGroupEntry UOptionalTournamentGroupEntryLibrary::MakeOptional(UTournamentGroupEntry* Value)
{
	FOptionalTournamentGroupEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalTournamentGroupEntry UOptionalTournamentGroupEntryLibrary::Conv_OptionalFromValue(UTournamentGroupEntry* Value)
{
	FOptionalTournamentGroupEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalTournamentGroupEntryLibrary::HasValue(const FOptionalTournamentGroupEntry& Optional, UTournamentGroupEntry*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UTournamentGroupEntry* UOptionalTournamentGroupEntryLibrary::GetOptionalValue(const FOptionalTournamentGroupEntry& Optional, UTournamentGroupEntry* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

