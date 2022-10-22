#include "OptionalStringLibrary.h"

FOptionalString UOptionalStringLibrary::MakeOptionalString(FString Value)
{
	FOptionalString Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalString UOptionalStringLibrary::Conv_OptionalStringFromValue(FString Value)
{
	FOptionalString Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalStringLibrary::HasValue(const FOptionalString& Optional, FString& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

FString UOptionalStringLibrary::GetValueWithFallback(const FOptionalString& Optional, const FString& DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}
