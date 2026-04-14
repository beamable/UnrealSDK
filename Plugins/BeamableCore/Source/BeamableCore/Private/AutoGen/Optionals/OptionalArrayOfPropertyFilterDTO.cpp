
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfPropertyFilterDTO.h"

FOptionalArrayOfPropertyFilterDTO::FOptionalArrayOfPropertyFilterDTO()
{
	Val = TArray<UPropertyFilterDTO*>();
	IsSet = false;
}

FOptionalArrayOfPropertyFilterDTO::FOptionalArrayOfPropertyFilterDTO(TArray<UPropertyFilterDTO*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfPropertyFilterDTO::GetAddr() const { return &Val; }

void FOptionalArrayOfPropertyFilterDTO::Set(const void* Data)
{
	Val = *((TArray<UPropertyFilterDTO*>*)Data);
	IsSet = true;
}