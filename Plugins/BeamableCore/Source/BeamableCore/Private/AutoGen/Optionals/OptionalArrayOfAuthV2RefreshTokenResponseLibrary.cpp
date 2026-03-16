

#include "AutoGen/Optionals/OptionalArrayOfAuthV2RefreshTokenResponseLibrary.h"

FOptionalArrayOfAuthV2RefreshTokenResponse UOptionalArrayOfAuthV2RefreshTokenResponseLibrary::MakeOptional(TArray<UAuthV2RefreshTokenResponse*> Value)
{
	FOptionalArrayOfAuthV2RefreshTokenResponse Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfAuthV2RefreshTokenResponse UOptionalArrayOfAuthV2RefreshTokenResponseLibrary::Conv_OptionalFromValue(TArray<UAuthV2RefreshTokenResponse*> Value)
{
	FOptionalArrayOfAuthV2RefreshTokenResponse Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfAuthV2RefreshTokenResponseLibrary::HasValue(const FOptionalArrayOfAuthV2RefreshTokenResponse& Optional, TArray<UAuthV2RefreshTokenResponse*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UAuthV2RefreshTokenResponse*> UOptionalArrayOfAuthV2RefreshTokenResponseLibrary::GetOptionalValue(const FOptionalArrayOfAuthV2RefreshTokenResponse& Optional, TArray<UAuthV2RefreshTokenResponse*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

