
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInventoryUpdateDelta.h"

FOptionalInventoryUpdateDelta::FOptionalInventoryUpdateDelta()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalInventoryUpdateDelta::FOptionalInventoryUpdateDelta(UInventoryUpdateDelta* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalInventoryUpdateDelta::GetAddr() const { return &Val; }

void FOptionalInventoryUpdateDelta::Set(const void* Data)
{
	Val = *((UInventoryUpdateDelta**)Data);
	IsSet = true;
}