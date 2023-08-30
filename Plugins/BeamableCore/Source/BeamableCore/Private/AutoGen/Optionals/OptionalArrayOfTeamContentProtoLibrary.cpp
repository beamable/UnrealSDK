

#include "AutoGen/Optionals/OptionalArrayOfTeamContentProtoLibrary.h"

FOptionalArrayOfTeamContentProto UOptionalArrayOfTeamContentProtoLibrary::MakeOptional(TArray<UTeamContentProto*> Value)
{
	FOptionalArrayOfTeamContentProto Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfTeamContentProto UOptionalArrayOfTeamContentProtoLibrary::Conv_OptionalFromValue(TArray<UTeamContentProto*> Value)
{
	FOptionalArrayOfTeamContentProto Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfTeamContentProtoLibrary::HasValue(const FOptionalArrayOfTeamContentProto& Optional, TArray<UTeamContentProto*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UTeamContentProto*> UOptionalArrayOfTeamContentProtoLibrary::GetOptionalValue(const FOptionalArrayOfTeamContentProto& Optional, TArray<UTeamContentProto*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

