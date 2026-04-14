

#include "AutoGen/Optionals/OptionalInventoryUpdateDeltaLibrary.h"

FOptionalInventoryUpdateDelta UOptionalInventoryUpdateDeltaLibrary::MakeOptional(UInventoryUpdateDelta* Value)
{
	FOptionalInventoryUpdateDelta Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalInventoryUpdateDelta UOptionalInventoryUpdateDeltaLibrary::Conv_OptionalFromValue(UInventoryUpdateDelta* Value)
{
	FOptionalInventoryUpdateDelta Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalInventoryUpdateDeltaLibrary::HasValue(const FOptionalInventoryUpdateDelta& Optional, UInventoryUpdateDelta*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UInventoryUpdateDelta* UOptionalInventoryUpdateDeltaLibrary::GetOptionalValue(const FOptionalInventoryUpdateDelta& Optional, UInventoryUpdateDelta* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

