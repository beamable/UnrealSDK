
#include "BeamableCore/Public/AutoGen/Optionals/OptionalSessionUser.h"

FOptionalSessionUser::FOptionalSessionUser()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalSessionUser::FOptionalSessionUser(USessionUser* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalSessionUser::GetAddr() const { return &Val; }

void FOptionalSessionUser::Set(const void* Data)
{
	Val = *((USessionUser**)Data);
	IsSet = true;
}