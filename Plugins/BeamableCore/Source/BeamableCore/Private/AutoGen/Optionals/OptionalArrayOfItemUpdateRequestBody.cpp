
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfItemUpdateRequestBody.h"

FOptionalArrayOfItemUpdateRequestBody::FOptionalArrayOfItemUpdateRequestBody()
{
	Val = TArray<UItemUpdateRequestBody*>();
	IsSet = false;
}

FOptionalArrayOfItemUpdateRequestBody::FOptionalArrayOfItemUpdateRequestBody(TArray<UItemUpdateRequestBody*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfItemUpdateRequestBody::GetAddr() const { return &Val; }

void FOptionalArrayOfItemUpdateRequestBody::Set(const void* Data)
{
	Val = *((TArray<UItemUpdateRequestBody*>*)Data);
	IsSet = true;
}