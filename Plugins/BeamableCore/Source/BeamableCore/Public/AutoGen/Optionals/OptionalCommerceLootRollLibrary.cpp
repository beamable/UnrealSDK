

#include "OptionalCommerceLootRollLibrary.h"

FOptionalCommerceLootRoll UOptionalCommerceLootRollLibrary::MakeOptionalCommerceLootRoll(UCommerceLootRoll* Value)
{
	FOptionalCommerceLootRoll Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalCommerceLootRoll UOptionalCommerceLootRollLibrary::Conv_OptionalCommerceLootRollFromValue(UCommerceLootRoll* Value)
{
	FOptionalCommerceLootRoll Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

