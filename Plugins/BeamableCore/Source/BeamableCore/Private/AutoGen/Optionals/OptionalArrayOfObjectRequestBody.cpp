
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfObjectRequestBody.h"

FOptionalArrayOfObjectRequestBody::FOptionalArrayOfObjectRequestBody()
{
	Val = TArray<UObjectRequestBody*>();
	IsSet = false;
}

FOptionalArrayOfObjectRequestBody::FOptionalArrayOfObjectRequestBody(TArray<UObjectRequestBody*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfObjectRequestBody::GetAddr() const { return &Val; }

void FOptionalArrayOfObjectRequestBody::Set(const void* Data)
{
	Val = *((TArray<UObjectRequestBody*>*)Data);
	IsSet = true;
}