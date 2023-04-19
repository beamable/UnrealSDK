
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfExternalIdentity.h"

FOptionalArrayOfExternalIdentity::FOptionalArrayOfExternalIdentity()
{
	Val = TArray<UExternalIdentity*>();
	IsSet = false;
}

FOptionalArrayOfExternalIdentity::FOptionalArrayOfExternalIdentity(TArray<UExternalIdentity*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfExternalIdentity::GetAddr() const { return &Val; }

void FOptionalArrayOfExternalIdentity::Set(const void* Data)
{
	Val = *((TArray<UExternalIdentity*>*)Data);
	IsSet = true;
}