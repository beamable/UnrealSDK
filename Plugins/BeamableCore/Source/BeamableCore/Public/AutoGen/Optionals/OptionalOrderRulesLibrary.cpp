

#include "OptionalOrderRulesLibrary.h"

FOptionalOrderRules UOptionalOrderRulesLibrary::MakeOptionalOrderRules(UOrderRules* Value)
{
	FOptionalOrderRules Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalOrderRules UOptionalOrderRulesLibrary::Conv_OptionalOrderRulesFromValue(UOrderRules* Value)
{
	FOptionalOrderRules Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

