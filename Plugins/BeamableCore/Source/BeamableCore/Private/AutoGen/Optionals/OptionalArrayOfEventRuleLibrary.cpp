

#include "AutoGen/Optionals/OptionalArrayOfEventRuleLibrary.h"

FOptionalArrayOfEventRule UOptionalArrayOfEventRuleLibrary::MakeOptional(TArray<UEventRule*> Value)
{
	FOptionalArrayOfEventRule Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfEventRule UOptionalArrayOfEventRuleLibrary::Conv_OptionalFromValue(TArray<UEventRule*> Value)
{
	FOptionalArrayOfEventRule Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfEventRuleLibrary::HasValue(const FOptionalArrayOfEventRule& Optional, TArray<UEventRule*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UEventRule*> UOptionalArrayOfEventRuleLibrary::GetOptionalValue(const FOptionalArrayOfEventRule& Optional, TArray<UEventRule*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

