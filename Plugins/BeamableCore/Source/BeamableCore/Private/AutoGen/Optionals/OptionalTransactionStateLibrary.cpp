

#include "AutoGen/Optionals/OptionalTransactionStateLibrary.h"

FOptionalTransactionState UOptionalTransactionStateLibrary::MakeOptional(EBeamTransactionState Value)
{
	FOptionalTransactionState Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalTransactionState UOptionalTransactionStateLibrary::Conv_OptionalFromValue(EBeamTransactionState Value)
{
	FOptionalTransactionState Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalTransactionStateLibrary::HasValue(const FOptionalTransactionState& Optional, EBeamTransactionState& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

EBeamTransactionState UOptionalTransactionStateLibrary::GetOptionalValue(const FOptionalTransactionState& Optional, EBeamTransactionState DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

