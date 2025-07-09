
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfLink.h"

FOptionalArrayOfLink::FOptionalArrayOfLink()
{
	Val = TArray<ULink*>();
	IsSet = false;
}

FOptionalArrayOfLink::FOptionalArrayOfLink(TArray<ULink*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfLink::GetAddr() const { return &Val; }

void FOptionalArrayOfLink::Set(const void* Data)
{
	Val = *((TArray<ULink*>*)Data);
	IsSet = true;
}