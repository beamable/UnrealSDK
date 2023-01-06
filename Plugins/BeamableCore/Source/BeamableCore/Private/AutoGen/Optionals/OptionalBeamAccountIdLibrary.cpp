

#include "AutoGen/Optionals/OptionalBeamAccountIdLibrary.h"

FOptionalBeamAccountId UOptionalBeamAccountIdLibrary::MakeOptional(FBeamAccountId Value)
{
	FOptionalBeamAccountId Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamAccountId UOptionalBeamAccountIdLibrary::Conv_OptionalFromValue(FBeamAccountId Value)
{
	FOptionalBeamAccountId Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamAccountIdLibrary::HasValue(const FOptionalBeamAccountId& Optional, FBeamAccountId& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

FBeamAccountId UOptionalBeamAccountIdLibrary::GetOptionalValue(const FOptionalBeamAccountId& Optional, FBeamAccountId DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

