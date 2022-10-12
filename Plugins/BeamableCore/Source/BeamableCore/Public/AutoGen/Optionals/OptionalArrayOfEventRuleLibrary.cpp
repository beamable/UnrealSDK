

#include "OptionalArrayOfEventRuleLibrary.h"

FOptionalArrayOfEventRule UOptionalArrayOfEventRuleLibrary::MakeOptionalArrayOfEventRule(TArray<UEventRule*> Value)
{
	FOptionalArrayOfEventRule Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfEventRule UOptionalArrayOfEventRuleLibrary::Conv_OptionalArrayOfEventRuleFromValue(TArray<UEventRule*> Value)
{
	FOptionalArrayOfEventRule Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

