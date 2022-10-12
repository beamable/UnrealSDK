

#include "OptionalArrayOfGroupScoreBindingLibrary.h"

FOptionalArrayOfGroupScoreBinding UOptionalArrayOfGroupScoreBindingLibrary::MakeOptionalArrayOfGroupScoreBinding(TArray<UGroupScoreBinding*> Value)
{
	FOptionalArrayOfGroupScoreBinding Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfGroupScoreBinding UOptionalArrayOfGroupScoreBindingLibrary::Conv_OptionalArrayOfGroupScoreBindingFromValue(TArray<UGroupScoreBinding*> Value)
{
	FOptionalArrayOfGroupScoreBinding Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

