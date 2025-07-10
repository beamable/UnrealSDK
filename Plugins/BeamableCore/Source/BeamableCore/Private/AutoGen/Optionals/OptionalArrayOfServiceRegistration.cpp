
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfServiceRegistration.h"

FOptionalArrayOfServiceRegistration::FOptionalArrayOfServiceRegistration()
{
	Val = TArray<UServiceRegistration*>();
	IsSet = false;
}

FOptionalArrayOfServiceRegistration::FOptionalArrayOfServiceRegistration(TArray<UServiceRegistration*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfServiceRegistration::GetAddr() const { return &Val; }

void FOptionalArrayOfServiceRegistration::Set(const void* Data)
{
	Val = *((TArray<UServiceRegistration*>*)Data);
	IsSet = true;
}