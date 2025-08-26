
#include "BeamableCore/Public/AutoGen/Optionals/OptionalTokenResponse.h"

FOptionalTokenResponse::FOptionalTokenResponse()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalTokenResponse::FOptionalTokenResponse(UTokenResponse* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalTokenResponse::GetAddr() const { return &Val; }

void FOptionalTokenResponse::Set(const void* Data)
{
	Val = *((UTokenResponse**)Data);
	IsSet = true;
}