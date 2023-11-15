

#include "AutoGen/Optionals/OptionalSessionLanguageContextLibrary.h"

FOptionalSessionLanguageContext UOptionalSessionLanguageContextLibrary::MakeOptional(USessionLanguageContext* Value)
{
	FOptionalSessionLanguageContext Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalSessionLanguageContext UOptionalSessionLanguageContextLibrary::Conv_OptionalFromValue(USessionLanguageContext* Value)
{
	FOptionalSessionLanguageContext Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalSessionLanguageContextLibrary::HasValue(const FOptionalSessionLanguageContext& Optional, USessionLanguageContext*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

USessionLanguageContext* UOptionalSessionLanguageContextLibrary::GetOptionalValue(const FOptionalSessionLanguageContext& Optional, USessionLanguageContext* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

