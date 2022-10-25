

#include "AutoGen/Optionals/OptionalTournamentEntryLibrary.h"

FOptionalTournamentEntry UOptionalTournamentEntryLibrary::MakeOptional(UTournamentEntry* Value)
{
	FOptionalTournamentEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalTournamentEntry UOptionalTournamentEntryLibrary::Conv_OptionalFromValue(UTournamentEntry* Value)
{
	FOptionalTournamentEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalTournamentEntryLibrary::HasValue(const FOptionalTournamentEntry& Optional, UTournamentEntry*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UTournamentEntry* UOptionalTournamentEntryLibrary::GetOptionalValue(const FOptionalTournamentEntry& Optional, UTournamentEntry* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

