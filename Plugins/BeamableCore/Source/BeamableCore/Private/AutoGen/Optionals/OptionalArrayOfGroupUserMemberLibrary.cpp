

#include "AutoGen/Optionals/OptionalArrayOfGroupUserMemberLibrary.h"

FOptionalArrayOfGroupUserMember UOptionalArrayOfGroupUserMemberLibrary::MakeOptional(TArray<UGroupUserMember*> Value)
{
	FOptionalArrayOfGroupUserMember Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfGroupUserMember UOptionalArrayOfGroupUserMemberLibrary::Conv_OptionalFromValue(TArray<UGroupUserMember*> Value)
{
	FOptionalArrayOfGroupUserMember Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfGroupUserMemberLibrary::HasValue(const FOptionalArrayOfGroupUserMember& Optional, TArray<UGroupUserMember*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UGroupUserMember*> UOptionalArrayOfGroupUserMemberLibrary::GetOptionalValue(const FOptionalArrayOfGroupUserMember& Optional, TArray<UGroupUserMember*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

