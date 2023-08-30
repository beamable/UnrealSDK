
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMatchType.h"

FOptionalMatchType::FOptionalMatchType()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalMatchType::FOptionalMatchType(UMatchType* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalMatchType::GetAddr() const { return &Val; }

void FOptionalMatchType::Set(const void* Data)
{
	Val = *((UMatchType**)Data);
	IsSet = true;
}