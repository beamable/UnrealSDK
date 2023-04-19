
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfServiceComponent.h"

FOptionalArrayOfServiceComponent::FOptionalArrayOfServiceComponent()
{
	Val = TArray<UServiceComponent*>();
	IsSet = false;
}

FOptionalArrayOfServiceComponent::FOptionalArrayOfServiceComponent(TArray<UServiceComponent*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfServiceComponent::GetAddr() const { return &Val; }

void FOptionalArrayOfServiceComponent::Set(const void* Data)
{
	Val = *((TArray<UServiceComponent*>*)Data);
	IsSet = true;
}