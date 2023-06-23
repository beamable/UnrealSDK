

#include "AutoGen/Optionals/OptionalArrayOfTeamLibrary.h"

FOptionalArrayOfTeam UOptionalArrayOfTeamLibrary::MakeOptional(TArray<UTeam*> Value)
{
	FOptionalArrayOfTeam Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfTeam UOptionalArrayOfTeamLibrary::Conv_OptionalFromValue(TArray<UTeam*> Value)
{
	FOptionalArrayOfTeam Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfTeamLibrary::HasValue(const FOptionalArrayOfTeam& Optional, TArray<UTeam*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UTeam*> UOptionalArrayOfTeamLibrary::GetOptionalValue(const FOptionalArrayOfTeam& Optional, TArray<UTeam*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

