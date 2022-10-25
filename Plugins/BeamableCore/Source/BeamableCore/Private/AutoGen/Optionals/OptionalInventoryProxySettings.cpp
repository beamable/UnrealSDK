
#include "AutoGen/Optionals/OptionalInventoryProxySettings.h"

FOptionalInventoryProxySettings::FOptionalInventoryProxySettings()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalInventoryProxySettings::FOptionalInventoryProxySettings(UInventoryProxySettings* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalInventoryProxySettings::GetAddr() const { return &Val; }

void FOptionalInventoryProxySettings::Set(const void* Data)
{
	Val = *((UInventoryProxySettings**)Data);
	IsSet = true;
}