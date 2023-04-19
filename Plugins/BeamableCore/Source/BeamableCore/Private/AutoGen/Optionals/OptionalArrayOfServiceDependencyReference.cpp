
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfServiceDependencyReference.h"

FOptionalArrayOfServiceDependencyReference::FOptionalArrayOfServiceDependencyReference()
{
	Val = TArray<UServiceDependencyReference*>();
	IsSet = false;
}

FOptionalArrayOfServiceDependencyReference::FOptionalArrayOfServiceDependencyReference(TArray<UServiceDependencyReference*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfServiceDependencyReference::GetAddr() const { return &Val; }

void FOptionalArrayOfServiceDependencyReference::Set(const void* Data)
{
	Val = *((TArray<UServiceDependencyReference*>*)Data);
	IsSet = true;
}