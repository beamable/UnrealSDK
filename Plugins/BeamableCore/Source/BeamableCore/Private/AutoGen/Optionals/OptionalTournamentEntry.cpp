
#include "BeamableCore/Public/AutoGen/Optionals/OptionalTournamentEntry.h"

FOptionalTournamentEntry::FOptionalTournamentEntry()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalTournamentEntry::FOptionalTournamentEntry(UTournamentEntry* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalTournamentEntry::GetAddr() const { return &Val; }

void FOptionalTournamentEntry::Set(const void* Data)
{
	Val = *((UTournamentEntry**)Data);
	IsSet = true;
}