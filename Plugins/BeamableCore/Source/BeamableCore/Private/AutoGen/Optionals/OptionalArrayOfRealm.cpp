
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfRealm.h"

FOptionalArrayOfRealm::FOptionalArrayOfRealm()
{
	Val = TArray<URealm*>();
	IsSet = false;
}

FOptionalArrayOfRealm::FOptionalArrayOfRealm(TArray<URealm*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfRealm::GetAddr() const { return &Val; }

void FOptionalArrayOfRealm::Set(const void* Data)
{
	Val = *((TArray<URealm*>*)Data);
	IsSet = true;
}