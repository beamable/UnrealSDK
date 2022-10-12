
#include "AutoGen/Optionals/OptionalClientPermission.h"

FOptionalClientPermission::FOptionalClientPermission()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalClientPermission::FOptionalClientPermission(UClientPermission* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalClientPermission::GetAddr() const { return &Val; }

void FOptionalClientPermission::Set(const void* Data)
{
	Val = *((UClientPermission**)Data);
	IsSet = true;
}