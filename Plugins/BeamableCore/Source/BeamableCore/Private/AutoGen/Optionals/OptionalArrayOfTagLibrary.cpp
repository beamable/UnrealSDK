

#include "AutoGen/Optionals/OptionalArrayOfTagLibrary.h"

FOptionalArrayOfTag UOptionalArrayOfTagLibrary::MakeOptional(TArray<UTag*> Value)
{
	FOptionalArrayOfTag Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfTag UOptionalArrayOfTagLibrary::Conv_OptionalFromValue(TArray<UTag*> Value)
{
	FOptionalArrayOfTag Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfTagLibrary::HasValue(const FOptionalArrayOfTag& Optional, TArray<UTag*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UTag*> UOptionalArrayOfTagLibrary::GetOptionalValue(const FOptionalArrayOfTag& Optional, TArray<UTag*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

