
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfString.h"

FOptionalMapOfString::FOptionalMapOfString()
{
	Val = TMap<FString, FString>();
	IsSet = false;
}

FOptionalMapOfString::FOptionalMapOfString(TMap<FString, FString> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalMapOfString::GetAddr() const { return &Val; }

void FOptionalMapOfString::Set(const void* Data)
{
	Val = *((TMap<FString, FString>*)Data);
	IsSet = true;
}