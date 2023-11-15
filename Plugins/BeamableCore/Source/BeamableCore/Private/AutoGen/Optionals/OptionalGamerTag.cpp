
#include "BeamableCore/Public/AutoGen/Optionals/OptionalGamerTag.h"

FOptionalGamerTag::FOptionalGamerTag()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalGamerTag::FOptionalGamerTag(UGamerTag* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalGamerTag::GetAddr() const { return &Val; }

void FOptionalGamerTag::Set(const void* Data)
{
	Val = *((UGamerTag**)Data);
	IsSet = true;
}