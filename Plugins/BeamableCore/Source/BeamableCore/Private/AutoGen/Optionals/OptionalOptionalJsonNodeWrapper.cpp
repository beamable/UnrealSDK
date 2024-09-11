
#include "BeamableCore/Public/AutoGen/Optionals/OptionalOptionalJsonNodeWrapper.h"

FOptionalOptionalJsonNodeWrapper::FOptionalOptionalJsonNodeWrapper()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalOptionalJsonNodeWrapper::FOptionalOptionalJsonNodeWrapper(UOptionalJsonNodeWrapper* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalOptionalJsonNodeWrapper::GetAddr() const { return &Val; }

void FOptionalOptionalJsonNodeWrapper::Set(const void* Data)
{
	Val = *((UOptionalJsonNodeWrapper**)Data);
	IsSet = true;
}