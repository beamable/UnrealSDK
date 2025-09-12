
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInventoryFiltersDTO.h"

FOptionalInventoryFiltersDTO::FOptionalInventoryFiltersDTO()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalInventoryFiltersDTO::FOptionalInventoryFiltersDTO(UInventoryFiltersDTO* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalInventoryFiltersDTO::GetAddr() const { return &Val; }

void FOptionalInventoryFiltersDTO::Set(const void* Data)
{
	Val = *((UInventoryFiltersDTO**)Data);
	IsSet = true;
}