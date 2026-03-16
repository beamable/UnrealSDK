

#include "AutoGen/Optionals/OptionalSessionLanguageContextDtoLibrary.h"

FOptionalSessionLanguageContextDto UOptionalSessionLanguageContextDtoLibrary::MakeOptional(USessionLanguageContextDto* Value)
{
	FOptionalSessionLanguageContextDto Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalSessionLanguageContextDto UOptionalSessionLanguageContextDtoLibrary::Conv_OptionalFromValue(USessionLanguageContextDto* Value)
{
	FOptionalSessionLanguageContextDto Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalSessionLanguageContextDtoLibrary::HasValue(const FOptionalSessionLanguageContextDto& Optional, USessionLanguageContextDto*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

USessionLanguageContextDto* UOptionalSessionLanguageContextDtoLibrary::GetOptionalValue(const FOptionalSessionLanguageContextDto& Optional, USessionLanguageContextDto* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

