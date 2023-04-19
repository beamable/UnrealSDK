
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArchetypeProxy.h"

FOptionalArchetypeProxy::FOptionalArchetypeProxy()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalArchetypeProxy::FOptionalArchetypeProxy(UArchetypeProxy* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArchetypeProxy::GetAddr() const { return &Val; }

void FOptionalArchetypeProxy::Set(const void* Data)
{
	Val = *((UArchetypeProxy**)Data);
	IsSet = true;
}