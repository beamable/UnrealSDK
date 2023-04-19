
#include "BeamableCore/Public/AutoGen/Optionals/OptionalCommerceLootRoll.h"

FOptionalCommerceLootRoll::FOptionalCommerceLootRoll()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalCommerceLootRoll::FOptionalCommerceLootRoll(UCommerceLootRoll* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalCommerceLootRoll::GetAddr() const { return &Val; }

void FOptionalCommerceLootRoll::Set(const void* Data)
{
	Val = *((UCommerceLootRoll**)Data);
	IsSet = true;
}