

#include "AutoGen/Optionals/OptionalCommerceLootRollLibrary.h"

FOptionalCommerceLootRoll UOptionalCommerceLootRollLibrary::MakeOptional(UCommerceLootRoll* Value)
{
	FOptionalCommerceLootRoll Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalCommerceLootRoll UOptionalCommerceLootRollLibrary::Conv_OptionalFromValue(UCommerceLootRoll* Value)
{
	FOptionalCommerceLootRoll Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalCommerceLootRollLibrary::HasValue(const FOptionalCommerceLootRoll& Optional, UCommerceLootRoll*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UCommerceLootRoll* UOptionalCommerceLootRollLibrary::GetOptionalValue(const FOptionalCommerceLootRoll& Optional, UCommerceLootRoll* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

