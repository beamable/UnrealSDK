
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfStringStringKeyValuePair.h"

FOptionalArrayOfStringStringKeyValuePair::FOptionalArrayOfStringStringKeyValuePair()
{
	Val = TArray<UStringStringKeyValuePair*>();
	IsSet = false;
}

FOptionalArrayOfStringStringKeyValuePair::FOptionalArrayOfStringStringKeyValuePair(TArray<UStringStringKeyValuePair*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfStringStringKeyValuePair::GetAddr() const { return &Val; }

void FOptionalArrayOfStringStringKeyValuePair::Set(const void* Data)
{
	Val = *((TArray<UStringStringKeyValuePair*>*)Data);
	IsSet = true;
}