

#include "AutoGen/Optionals/OptionalArrayOfMessageLibrary.h"

FOptionalArrayOfMessage UOptionalArrayOfMessageLibrary::MakeOptional(TArray<UMessage*> Value)
{
	FOptionalArrayOfMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfMessage UOptionalArrayOfMessageLibrary::Conv_OptionalFromValue(TArray<UMessage*> Value)
{
	FOptionalArrayOfMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfMessageLibrary::HasValue(const FOptionalArrayOfMessage& Optional, TArray<UMessage*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UMessage*> UOptionalArrayOfMessageLibrary::GetOptionalValue(const FOptionalArrayOfMessage& Optional, TArray<UMessage*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

