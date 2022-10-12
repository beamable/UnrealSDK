

#include "OptionalTournamentGroupEntryLibrary.h"

FOptionalTournamentGroupEntry UOptionalTournamentGroupEntryLibrary::MakeOptionalTournamentGroupEntry(UTournamentGroupEntry* Value)
{
	FOptionalTournamentGroupEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalTournamentGroupEntry UOptionalTournamentGroupEntryLibrary::Conv_OptionalTournamentGroupEntryFromValue(UTournamentGroupEntry* Value)
{
	FOptionalTournamentGroupEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

