

#include "OptionalArrayOfStatStringListEntryLibrary.h"

FOptionalArrayOfStatStringListEntry UOptionalArrayOfStatStringListEntryLibrary::MakeOptionalArrayOfStatStringListEntry(TArray<UStatStringListEntry*> Value)
{
	FOptionalArrayOfStatStringListEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfStatStringListEntry UOptionalArrayOfStatStringListEntryLibrary::Conv_OptionalArrayOfStatStringListEntryFromValue(TArray<UStatStringListEntry*> Value)
{
	FOptionalArrayOfStatStringListEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

