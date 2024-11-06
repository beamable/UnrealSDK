
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfSupportedFederation.h"

FOptionalArrayOfSupportedFederation::FOptionalArrayOfSupportedFederation()
{
	Val = TArray<USupportedFederation*>();
	IsSet = false;
}

FOptionalArrayOfSupportedFederation::FOptionalArrayOfSupportedFederation(TArray<USupportedFederation*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfSupportedFederation::GetAddr() const { return &Val; }

void FOptionalArrayOfSupportedFederation::Set(const void* Data)
{
	Val = *((TArray<USupportedFederation*>*)Data);
	IsSet = true;
}