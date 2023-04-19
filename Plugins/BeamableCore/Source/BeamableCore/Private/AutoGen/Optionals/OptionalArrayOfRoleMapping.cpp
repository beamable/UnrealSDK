
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfRoleMapping.h"

FOptionalArrayOfRoleMapping::FOptionalArrayOfRoleMapping()
{
	Val = TArray<URoleMapping*>();
	IsSet = false;
}

FOptionalArrayOfRoleMapping::FOptionalArrayOfRoleMapping(TArray<URoleMapping*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfRoleMapping::GetAddr() const { return &Val; }

void FOptionalArrayOfRoleMapping::Set(const void* Data)
{
	Val = *((TArray<URoleMapping*>*)Data);
	IsSet = true;
}