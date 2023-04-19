
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfServiceStorageReference.h"

FOptionalArrayOfServiceStorageReference::FOptionalArrayOfServiceStorageReference()
{
	Val = TArray<UServiceStorageReference*>();
	IsSet = false;
}

FOptionalArrayOfServiceStorageReference::FOptionalArrayOfServiceStorageReference(TArray<UServiceStorageReference*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfServiceStorageReference::GetAddr() const { return &Val; }

void FOptionalArrayOfServiceStorageReference::Set(const void* Data)
{
	Val = *((TArray<UServiceStorageReference*>*)Data);
	IsSet = true;
}