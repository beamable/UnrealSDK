
#include "BeamableCore/Public/AutoGen/Optionals/OptionalGatewayLimits.h"

FOptionalGatewayLimits::FOptionalGatewayLimits()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalGatewayLimits::FOptionalGatewayLimits(UGatewayLimits* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalGatewayLimits::GetAddr() const { return &Val; }

void FOptionalGatewayLimits::Set(const void* Data)
{
	Val = *((UGatewayLimits**)Data);
	IsSet = true;
}