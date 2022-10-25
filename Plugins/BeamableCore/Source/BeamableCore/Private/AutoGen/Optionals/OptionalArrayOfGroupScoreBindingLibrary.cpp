

#include "AutoGen/Optionals/OptionalArrayOfGroupScoreBindingLibrary.h"

FOptionalArrayOfGroupScoreBinding UOptionalArrayOfGroupScoreBindingLibrary::MakeOptional(TArray<UGroupScoreBinding*> Value)
{
	FOptionalArrayOfGroupScoreBinding Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfGroupScoreBinding UOptionalArrayOfGroupScoreBindingLibrary::Conv_OptionalFromValue(TArray<UGroupScoreBinding*> Value)
{
	FOptionalArrayOfGroupScoreBinding Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfGroupScoreBindingLibrary::HasValue(const FOptionalArrayOfGroupScoreBinding& Optional, TArray<UGroupScoreBinding*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UGroupScoreBinding*> UOptionalArrayOfGroupScoreBindingLibrary::GetOptionalValue(const FOptionalArrayOfGroupScoreBinding& Optional, TArray<UGroupScoreBinding*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

