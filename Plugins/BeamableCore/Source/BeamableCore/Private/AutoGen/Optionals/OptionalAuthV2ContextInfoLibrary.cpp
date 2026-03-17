

#include "AutoGen/Optionals/OptionalAuthV2ContextInfoLibrary.h"

FOptionalAuthV2ContextInfo UOptionalAuthV2ContextInfoLibrary::MakeOptional(UAuthV2ContextInfo* Value)
{
	FOptionalAuthV2ContextInfo Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalAuthV2ContextInfo UOptionalAuthV2ContextInfoLibrary::Conv_OptionalFromValue(UAuthV2ContextInfo* Value)
{
	FOptionalAuthV2ContextInfo Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalAuthV2ContextInfoLibrary::HasValue(const FOptionalAuthV2ContextInfo& Optional, UAuthV2ContextInfo*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UAuthV2ContextInfo* UOptionalAuthV2ContextInfoLibrary::GetOptionalValue(const FOptionalAuthV2ContextInfo& Optional, UAuthV2ContextInfo* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

