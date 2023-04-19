
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfMapOfContentMeta.h"

FOptionalArrayOfMapOfContentMeta::FOptionalArrayOfMapOfContentMeta()
{
	Val = TArray<FMapOfContentMeta>();
	IsSet = false;
}

FOptionalArrayOfMapOfContentMeta::FOptionalArrayOfMapOfContentMeta(TArray<FMapOfContentMeta> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfMapOfContentMeta::GetAddr() const { return &Val; }

void FOptionalArrayOfMapOfContentMeta::Set(const void* Data)
{
	Val = *((TArray<FMapOfContentMeta>*)Data);
	IsSet = true;
}