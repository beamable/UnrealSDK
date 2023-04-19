
#include "BeamableCore/Public/AutoGen/Optionals/OptionalVariableReference.h"

FOptionalVariableReference::FOptionalVariableReference()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalVariableReference::FOptionalVariableReference(UVariableReference* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalVariableReference::GetAddr() const { return &Val; }

void FOptionalVariableReference::Set(const void* Data)
{
	Val = *((UVariableReference**)Data);
	IsSet = true;
}