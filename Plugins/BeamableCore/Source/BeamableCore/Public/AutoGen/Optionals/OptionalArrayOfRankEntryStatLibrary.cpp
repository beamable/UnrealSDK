

#include "OptionalArrayOfRankEntryStatLibrary.h"

FOptionalArrayOfRankEntryStat UOptionalArrayOfRankEntryStatLibrary::MakeOptionalArrayOfRankEntryStat(TArray<URankEntryStat*> Value)
{
	FOptionalArrayOfRankEntryStat Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfRankEntryStat UOptionalArrayOfRankEntryStatLibrary::Conv_OptionalArrayOfRankEntryStatFromValue(TArray<URankEntryStat*> Value)
{
	FOptionalArrayOfRankEntryStat Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

