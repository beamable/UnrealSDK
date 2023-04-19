
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"

FOptionalArrayOfString::FOptionalArrayOfString()
{
	Val = TArray<FString>();
	IsSet = false;
}

FOptionalArrayOfString::FOptionalArrayOfString(TArray<FString> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfString::GetAddr() const { return &Val; }

void FOptionalArrayOfString::Set(const void* Data)
{
	Val = *((TArray<FString>*)Data);
	IsSet = true;
}