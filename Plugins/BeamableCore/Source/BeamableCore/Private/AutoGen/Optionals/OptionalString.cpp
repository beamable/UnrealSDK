
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

FOptionalString::FOptionalString()
{
	Val = FString();
	IsSet = false;
}

FOptionalString::FOptionalString(FString Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalString::GetAddr() const { return &Val; }

void FOptionalString::Set(const void* Data)
{
	Val = *((FString*)Data);
	IsSet = true;
}