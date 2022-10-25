

#include "AutoGen/Optionals/OptionalRankEntryLibrary.h"

FOptionalRankEntry UOptionalRankEntryLibrary::MakeOptional(URankEntry* Value)
{
	FOptionalRankEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalRankEntry UOptionalRankEntryLibrary::Conv_OptionalFromValue(URankEntry* Value)
{
	FOptionalRankEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalRankEntryLibrary::HasValue(const FOptionalRankEntry& Optional, URankEntry*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

URankEntry* UOptionalRankEntryLibrary::GetOptionalValue(const FOptionalRankEntry& Optional, URankEntry* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

