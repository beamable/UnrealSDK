

#include "AutoGen/Optionals/OptionalArchetypeProxyLibrary.h"

FOptionalArchetypeProxy UOptionalArchetypeProxyLibrary::MakeOptional(UArchetypeProxy* Value)
{
	FOptionalArchetypeProxy Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArchetypeProxy UOptionalArchetypeProxyLibrary::Conv_OptionalFromValue(UArchetypeProxy* Value)
{
	FOptionalArchetypeProxy Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArchetypeProxyLibrary::HasValue(const FOptionalArchetypeProxy& Optional, UArchetypeProxy*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UArchetypeProxy* UOptionalArchetypeProxyLibrary::GetOptionalValue(const FOptionalArchetypeProxy& Optional, UArchetypeProxy* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

