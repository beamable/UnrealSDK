

#include "AutoGen/Optionals/OptionalArrayOfStatStringListEntryLibrary.h"

FOptionalArrayOfStatStringListEntry UOptionalArrayOfStatStringListEntryLibrary::MakeOptional(TArray<UStatStringListEntry*> Value)
{
	FOptionalArrayOfStatStringListEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfStatStringListEntry UOptionalArrayOfStatStringListEntryLibrary::Conv_OptionalFromValue(TArray<UStatStringListEntry*> Value)
{
	FOptionalArrayOfStatStringListEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfStatStringListEntryLibrary::HasValue(const FOptionalArrayOfStatStringListEntry& Optional, TArray<UStatStringListEntry*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UStatStringListEntry*> UOptionalArrayOfStatStringListEntryLibrary::GetOptionalValue(const FOptionalArrayOfStatStringListEntry& Optional, TArray<UStatStringListEntry*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

