

#include "AutoGen/Optionals/OptionalArrayOfRankEntryStatLibrary.h"

FOptionalArrayOfRankEntryStat UOptionalArrayOfRankEntryStatLibrary::MakeOptional(TArray<URankEntryStat*> Value)
{
	FOptionalArrayOfRankEntryStat Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfRankEntryStat UOptionalArrayOfRankEntryStatLibrary::Conv_OptionalFromValue(TArray<URankEntryStat*> Value)
{
	FOptionalArrayOfRankEntryStat Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfRankEntryStatLibrary::HasValue(const FOptionalArrayOfRankEntryStat& Optional, TArray<URankEntryStat*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<URankEntryStat*> UOptionalArrayOfRankEntryStatLibrary::GetOptionalValue(const FOptionalArrayOfRankEntryStat& Optional, TArray<URankEntryStat*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

