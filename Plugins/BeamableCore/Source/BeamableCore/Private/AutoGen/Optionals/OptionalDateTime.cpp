
#include "BeamableCore/Public/AutoGen/Optionals/OptionalDateTime.h"

FOptionalDateTime::FOptionalDateTime()
{
	Val = FDateTime();
	IsSet = false;
}

FOptionalDateTime::FOptionalDateTime(FDateTime Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalDateTime::GetAddr() const { return &Val; }

void FOptionalDateTime::Set(const void* Data)
{
	Val = *((FDateTime*)Data);
	IsSet = true;
}