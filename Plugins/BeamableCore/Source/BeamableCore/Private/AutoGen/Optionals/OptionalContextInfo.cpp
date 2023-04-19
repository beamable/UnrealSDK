
#include "BeamableCore/Public/AutoGen/Optionals/OptionalContextInfo.h"

FOptionalContextInfo::FOptionalContextInfo()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalContextInfo::FOptionalContextInfo(UContextInfo* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalContextInfo::GetAddr() const { return &Val; }

void FOptionalContextInfo::Set(const void* Data)
{
	Val = *((UContextInfo**)Data);
	IsSet = true;
}