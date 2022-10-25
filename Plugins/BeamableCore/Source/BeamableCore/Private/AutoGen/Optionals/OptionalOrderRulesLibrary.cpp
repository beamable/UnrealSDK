

#include "AutoGen/Optionals/OptionalOrderRulesLibrary.h"

FOptionalOrderRules UOptionalOrderRulesLibrary::MakeOptional(UOrderRules* Value)
{
	FOptionalOrderRules Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalOrderRules UOptionalOrderRulesLibrary::Conv_OptionalFromValue(UOrderRules* Value)
{
	FOptionalOrderRules Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalOrderRulesLibrary::HasValue(const FOptionalOrderRules& Optional, UOrderRules*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UOrderRules* UOptionalOrderRulesLibrary::GetOptionalValue(const FOptionalOrderRules& Optional, UOrderRules* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

