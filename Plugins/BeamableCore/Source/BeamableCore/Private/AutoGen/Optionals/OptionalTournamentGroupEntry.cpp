
#include "BeamableCore/Public/AutoGen/Optionals/OptionalTournamentGroupEntry.h"

FOptionalTournamentGroupEntry::FOptionalTournamentGroupEntry()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalTournamentGroupEntry::FOptionalTournamentGroupEntry(UTournamentGroupEntry* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalTournamentGroupEntry::GetAddr() const { return &Val; }

void FOptionalTournamentGroupEntry::Set(const void* Data)
{
	Val = *((UTournamentGroupEntry**)Data);
	IsSet = true;
}