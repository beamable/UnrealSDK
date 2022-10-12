

#include "OptionalTournamentEntryLibrary.h"

FOptionalTournamentEntry UOptionalTournamentEntryLibrary::MakeOptionalTournamentEntry(UTournamentEntry* Value)
{
	FOptionalTournamentEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalTournamentEntry UOptionalTournamentEntryLibrary::Conv_OptionalTournamentEntryFromValue(UTournamentEntry* Value)
{
	FOptionalTournamentEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

