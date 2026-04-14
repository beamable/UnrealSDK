

#include "AutoGen/Optionals/OptionalMapOfTagListLibrary.h"

FOptionalMapOfTagList UOptionalMapOfTagListLibrary::MakeOptional(TMap<FString, UTagList*> Value)
{
	FOptionalMapOfTagList Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMapOfTagList UOptionalMapOfTagListLibrary::Conv_OptionalFromValue(TMap<FString, UTagList*> Value)
{
	FOptionalMapOfTagList Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalMapOfTagListLibrary::HasValue(const FOptionalMapOfTagList& Optional, TMap<FString, UTagList*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TMap<FString, UTagList*> UOptionalMapOfTagListLibrary::GetOptionalValue(const FOptionalMapOfTagList& Optional, TMap<FString, UTagList*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

