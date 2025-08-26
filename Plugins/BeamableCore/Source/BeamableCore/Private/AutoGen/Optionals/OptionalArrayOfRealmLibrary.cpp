

#include "AutoGen/Optionals/OptionalArrayOfRealmLibrary.h"

FOptionalArrayOfRealm UOptionalArrayOfRealmLibrary::MakeOptional(TArray<URealm*> Value)
{
	FOptionalArrayOfRealm Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfRealm UOptionalArrayOfRealmLibrary::Conv_OptionalFromValue(TArray<URealm*> Value)
{
	FOptionalArrayOfRealm Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfRealmLibrary::HasValue(const FOptionalArrayOfRealm& Optional, TArray<URealm*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<URealm*> UOptionalArrayOfRealmLibrary::GetOptionalValue(const FOptionalArrayOfRealm& Optional, TArray<URealm*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

