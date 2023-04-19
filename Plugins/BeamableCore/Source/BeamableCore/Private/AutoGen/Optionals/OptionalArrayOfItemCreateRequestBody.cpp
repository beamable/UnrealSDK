
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfItemCreateRequestBody.h"

FOptionalArrayOfItemCreateRequestBody::FOptionalArrayOfItemCreateRequestBody()
{
	Val = TArray<UItemCreateRequestBody*>();
	IsSet = false;
}

FOptionalArrayOfItemCreateRequestBody::FOptionalArrayOfItemCreateRequestBody(TArray<UItemCreateRequestBody*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfItemCreateRequestBody::GetAddr() const { return &Val; }

void FOptionalArrayOfItemCreateRequestBody::Set(const void* Data)
{
	Val = *((TArray<UItemCreateRequestBody*>*)Data);
	IsSet = true;
}