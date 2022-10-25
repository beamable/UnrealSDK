

#include "AutoGen/Optionals/OptionalStringLibrary.h"

FOptionalString UOptionalStringLibrary::MakeOptional(FString Value)
{
	FOptionalString Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalString UOptionalStringLibrary::Conv_OptionalFromValue(FString Value)
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

FString UOptionalStringLibrary::GetOptionalValue(const FOptionalString& Optional, FString DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

