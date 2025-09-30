

#include "AutoGen/Optionals/OptionalArrayOfRealmViewLibrary.h"

FOptionalArrayOfRealmView UOptionalArrayOfRealmViewLibrary::MakeOptional(TArray<URealmView*> Value)
{
	FOptionalArrayOfRealmView Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfRealmView UOptionalArrayOfRealmViewLibrary::Conv_OptionalFromValue(TArray<URealmView*> Value)
{
	FOptionalArrayOfRealmView Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfRealmViewLibrary::HasValue(const FOptionalArrayOfRealmView& Optional, TArray<URealmView*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<URealmView*> UOptionalArrayOfRealmViewLibrary::GetOptionalValue(const FOptionalArrayOfRealmView& Optional, TArray<URealmView*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

