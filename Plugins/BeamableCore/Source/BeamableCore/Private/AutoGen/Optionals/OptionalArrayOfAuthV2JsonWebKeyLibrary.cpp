

#include "AutoGen/Optionals/OptionalArrayOfAuthV2JsonWebKeyLibrary.h"

FOptionalArrayOfAuthV2JsonWebKey UOptionalArrayOfAuthV2JsonWebKeyLibrary::MakeOptional(TArray<UAuthV2JsonWebKey*> Value)
{
	FOptionalArrayOfAuthV2JsonWebKey Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfAuthV2JsonWebKey UOptionalArrayOfAuthV2JsonWebKeyLibrary::Conv_OptionalFromValue(TArray<UAuthV2JsonWebKey*> Value)
{
	FOptionalArrayOfAuthV2JsonWebKey Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfAuthV2JsonWebKeyLibrary::HasValue(const FOptionalArrayOfAuthV2JsonWebKey& Optional, TArray<UAuthV2JsonWebKey*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UAuthV2JsonWebKey*> UOptionalArrayOfAuthV2JsonWebKeyLibrary::GetOptionalValue(const FOptionalArrayOfAuthV2JsonWebKey& Optional, TArray<UAuthV2JsonWebKey*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

