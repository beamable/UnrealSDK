

#include "OptionalRankEntryLibrary.h"

FOptionalRankEntry UOptionalRankEntryLibrary::MakeOptionalRankEntry(URankEntry* Value)
{
	FOptionalRankEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalRankEntry UOptionalRankEntryLibrary::Conv_OptionalRankEntryFromValue(URankEntry* Value)
{
	FOptionalRankEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

