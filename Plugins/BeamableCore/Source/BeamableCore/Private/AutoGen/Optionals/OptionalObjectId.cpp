
#include "BeamableCore/Public/AutoGen/Optionals/OptionalObjectId.h"

FOptionalObjectId::FOptionalObjectId()
{
	Val = NewObject<UObjectId>(GetTransientPackage());
	IsSet = false;
}

FOptionalObjectId::FOptionalObjectId(UObjectId* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalObjectId::GetAddr() const { return &Val; }

void FOptionalObjectId::Set(const void* Data)
{
	Val = *((UObjectId**)Data);
	IsSet = true;
}