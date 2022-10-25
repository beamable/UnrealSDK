

#include "AutoGen/Optionals/OptionalInventoryProxySettingsLibrary.h"

FOptionalInventoryProxySettings UOptionalInventoryProxySettingsLibrary::MakeOptional(UInventoryProxySettings* Value)
{
	FOptionalInventoryProxySettings Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalInventoryProxySettings UOptionalInventoryProxySettingsLibrary::Conv_OptionalFromValue(UInventoryProxySettings* Value)
{
	FOptionalInventoryProxySettings Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalInventoryProxySettingsLibrary::HasValue(const FOptionalInventoryProxySettings& Optional, UInventoryProxySettings*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UInventoryProxySettings* UOptionalInventoryProxySettingsLibrary::GetOptionalValue(const FOptionalInventoryProxySettings& Optional, UInventoryProxySettings* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

