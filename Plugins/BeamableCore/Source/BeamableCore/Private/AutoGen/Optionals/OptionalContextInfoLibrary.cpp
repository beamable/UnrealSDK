

#include "AutoGen/Optionals/OptionalContextInfoLibrary.h"

FOptionalContextInfo UOptionalContextInfoLibrary::MakeOptional(UContextInfo* Value)
{
	FOptionalContextInfo Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalContextInfo UOptionalContextInfoLibrary::Conv_OptionalFromValue(UContextInfo* Value)
{
	FOptionalContextInfo Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalContextInfoLibrary::HasValue(const FOptionalContextInfo& Optional, UContextInfo*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UContextInfo* UOptionalContextInfoLibrary::GetOptionalValue(const FOptionalContextInfo& Optional, UContextInfo* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

