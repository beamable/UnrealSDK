
#include "BeamableCore/Public/AutoGen/Optionals/OptionalAuthV2ContextInfo.h"

FOptionalAuthV2ContextInfo::FOptionalAuthV2ContextInfo()
{
	Val = NewObject<UAuthV2ContextInfo>(GetTransientPackage());
	IsSet = false;
}

FOptionalAuthV2ContextInfo::FOptionalAuthV2ContextInfo(UAuthV2ContextInfo* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalAuthV2ContextInfo::GetAddr() const { return &Val; }

void FOptionalAuthV2ContextInfo::Set(const void* Data)
{
	Val = *((UAuthV2ContextInfo**)Data);
	IsSet = true;
}