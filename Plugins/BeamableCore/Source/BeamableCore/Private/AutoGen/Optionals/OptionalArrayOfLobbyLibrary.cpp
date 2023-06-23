

#include "AutoGen/Optionals/OptionalArrayOfLobbyLibrary.h"

FOptionalArrayOfLobby UOptionalArrayOfLobbyLibrary::MakeOptional(TArray<ULobby*> Value)
{
	FOptionalArrayOfLobby Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfLobby UOptionalArrayOfLobbyLibrary::Conv_OptionalFromValue(TArray<ULobby*> Value)
{
	FOptionalArrayOfLobby Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfLobbyLibrary::HasValue(const FOptionalArrayOfLobby& Optional, TArray<ULobby*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<ULobby*> UOptionalArrayOfLobbyLibrary::GetOptionalValue(const FOptionalArrayOfLobby& Optional, TArray<ULobby*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

