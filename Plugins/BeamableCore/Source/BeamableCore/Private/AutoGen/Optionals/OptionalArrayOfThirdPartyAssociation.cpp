
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfThirdPartyAssociation.h"

FOptionalArrayOfThirdPartyAssociation::FOptionalArrayOfThirdPartyAssociation()
{
	Val = TArray<UThirdPartyAssociation*>();
	IsSet = false;
}

FOptionalArrayOfThirdPartyAssociation::FOptionalArrayOfThirdPartyAssociation(TArray<UThirdPartyAssociation*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfThirdPartyAssociation::GetAddr() const { return &Val; }

void FOptionalArrayOfThirdPartyAssociation::Set(const void* Data)
{
	Val = *((TArray<UThirdPartyAssociation*>*)Data);
	IsSet = true;
}