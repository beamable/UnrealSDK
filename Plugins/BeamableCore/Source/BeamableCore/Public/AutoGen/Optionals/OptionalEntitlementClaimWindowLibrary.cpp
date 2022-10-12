

#include "OptionalEntitlementClaimWindowLibrary.h"

FOptionalEntitlementClaimWindow UOptionalEntitlementClaimWindowLibrary::MakeOptionalEntitlementClaimWindow(UEntitlementClaimWindow* Value)
{
	FOptionalEntitlementClaimWindow Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalEntitlementClaimWindow UOptionalEntitlementClaimWindowLibrary::Conv_OptionalEntitlementClaimWindowFromValue(UEntitlementClaimWindow* Value)
{
	FOptionalEntitlementClaimWindow Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

