
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfRoleAssociation.h"

FOptionalArrayOfRoleAssociation::FOptionalArrayOfRoleAssociation()
{
	Val = TArray<URoleAssociation*>();
	IsSet = false;
}

FOptionalArrayOfRoleAssociation::FOptionalArrayOfRoleAssociation(TArray<URoleAssociation*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfRoleAssociation::GetAddr() const { return &Val; }

void FOptionalArrayOfRoleAssociation::Set(const void* Data)
{
	Val = *((TArray<URoleAssociation*>*)Data);
	IsSet = true;
}