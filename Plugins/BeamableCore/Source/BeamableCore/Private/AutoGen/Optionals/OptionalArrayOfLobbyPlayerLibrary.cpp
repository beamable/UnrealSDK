

#include "AutoGen/Optionals/OptionalArrayOfLobbyPlayerLibrary.h"

FOptionalArrayOfLobbyPlayer UOptionalArrayOfLobbyPlayerLibrary::MakeOptional(TArray<ULobbyPlayer*> Value)
{
	FOptionalArrayOfLobbyPlayer Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfLobbyPlayer UOptionalArrayOfLobbyPlayerLibrary::Conv_OptionalFromValue(TArray<ULobbyPlayer*> Value)
{
	FOptionalArrayOfLobbyPlayer Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfLobbyPlayerLibrary::HasValue(const FOptionalArrayOfLobbyPlayer& Optional, TArray<ULobbyPlayer*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<ULobbyPlayer*> UOptionalArrayOfLobbyPlayerLibrary::GetOptionalValue(const FOptionalArrayOfLobbyPlayer& Optional, TArray<ULobbyPlayer*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

