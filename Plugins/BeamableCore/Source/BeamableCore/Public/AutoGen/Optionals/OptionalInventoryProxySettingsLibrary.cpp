

#include "OptionalInventoryProxySettingsLibrary.h"

FOptionalInventoryProxySettings UOptionalInventoryProxySettingsLibrary::MakeOptionalInventoryProxySettings(UInventoryProxySettings* Value)
{
	FOptionalInventoryProxySettings Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalInventoryProxySettings UOptionalInventoryProxySettingsLibrary::Conv_OptionalInventoryProxySettingsFromValue(UInventoryProxySettings* Value)
{
	FOptionalInventoryProxySettings Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

