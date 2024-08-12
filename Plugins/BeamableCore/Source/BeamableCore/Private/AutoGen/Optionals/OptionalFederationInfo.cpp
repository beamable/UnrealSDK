
#include "BeamableCore/Public/AutoGen/Optionals/OptionalFederationInfo.h"

FOptionalFederationInfo::FOptionalFederationInfo()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalFederationInfo::FOptionalFederationInfo(UFederationInfo* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalFederationInfo::GetAddr() const { return &Val; }

void FOptionalFederationInfo::Set(const void* Data)
{
	Val = *((UFederationInfo**)Data);
	IsSet = true;
}