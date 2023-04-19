
#include "BeamableCore/Public/AutoGen/Optionals/OptionalEntitlementClaimWindow.h"

FOptionalEntitlementClaimWindow::FOptionalEntitlementClaimWindow()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalEntitlementClaimWindow::FOptionalEntitlementClaimWindow(UEntitlementClaimWindow* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalEntitlementClaimWindow::GetAddr() const { return &Val; }

void FOptionalEntitlementClaimWindow::Set(const void* Data)
{
	Val = *((UEntitlementClaimWindow**)Data);
	IsSet = true;
}