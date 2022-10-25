

#include "AutoGen/Optionals/OptionalEntitlementClaimWindowLibrary.h"

FOptionalEntitlementClaimWindow UOptionalEntitlementClaimWindowLibrary::MakeOptional(UEntitlementClaimWindow* Value)
{
	FOptionalEntitlementClaimWindow Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalEntitlementClaimWindow UOptionalEntitlementClaimWindowLibrary::Conv_OptionalFromValue(UEntitlementClaimWindow* Value)
{
	FOptionalEntitlementClaimWindow Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalEntitlementClaimWindowLibrary::HasValue(const FOptionalEntitlementClaimWindow& Optional, UEntitlementClaimWindow*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UEntitlementClaimWindow* UOptionalEntitlementClaimWindowLibrary::GetOptionalValue(const FOptionalEntitlementClaimWindow& Optional, UEntitlementClaimWindow* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

