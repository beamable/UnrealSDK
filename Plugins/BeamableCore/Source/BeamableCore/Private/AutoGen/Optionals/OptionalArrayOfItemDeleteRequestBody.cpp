
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfItemDeleteRequestBody.h"

FOptionalArrayOfItemDeleteRequestBody::FOptionalArrayOfItemDeleteRequestBody()
{
	Val = TArray<UItemDeleteRequestBody*>();
	IsSet = false;
}

FOptionalArrayOfItemDeleteRequestBody::FOptionalArrayOfItemDeleteRequestBody(TArray<UItemDeleteRequestBody*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfItemDeleteRequestBody::GetAddr() const { return &Val; }

void FOptionalArrayOfItemDeleteRequestBody::Set(const void* Data)
{
	Val = *((TArray<UItemDeleteRequestBody*>*)Data);
	IsSet = true;
}