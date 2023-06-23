
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfTag.h"

FOptionalArrayOfTag::FOptionalArrayOfTag()
{
	Val = TArray<UTag*>();
	IsSet = false;
}

FOptionalArrayOfTag::FOptionalArrayOfTag(TArray<UTag*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfTag::GetAddr() const { return &Val; }

void FOptionalArrayOfTag::Set(const void* Data)
{
	Val = *((TArray<UTag*>*)Data);
	IsSet = true;
}