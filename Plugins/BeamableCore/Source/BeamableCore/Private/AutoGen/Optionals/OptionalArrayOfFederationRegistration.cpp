
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfFederationRegistration.h"

FOptionalArrayOfFederationRegistration::FOptionalArrayOfFederationRegistration()
{
	Val = TArray<UFederationRegistration*>();
	IsSet = false;
}

FOptionalArrayOfFederationRegistration::FOptionalArrayOfFederationRegistration(TArray<UFederationRegistration*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfFederationRegistration::GetAddr() const { return &Val; }

void FOptionalArrayOfFederationRegistration::Set(const void* Data)
{
	Val = *((TArray<UFederationRegistration*>*)Data);
	IsSet = true;
}