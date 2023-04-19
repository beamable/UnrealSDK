
#include "BeamableCore/Public/AutoGen/Optionals/OptionalOrderRules.h"

FOptionalOrderRules::FOptionalOrderRules()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalOrderRules::FOptionalOrderRules(UOrderRules* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalOrderRules::GetAddr() const { return &Val; }

void FOptionalOrderRules::Set(const void* Data)
{
	Val = *((UOrderRules**)Data);
	IsSet = true;
}