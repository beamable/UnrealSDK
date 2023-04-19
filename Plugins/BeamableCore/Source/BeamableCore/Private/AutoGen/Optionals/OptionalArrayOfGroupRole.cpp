
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfGroupRole.h"

FOptionalArrayOfGroupRole::FOptionalArrayOfGroupRole()
{
	Val = TArray<UGroupRole*>();
	IsSet = false;
}

FOptionalArrayOfGroupRole::FOptionalArrayOfGroupRole(TArray<UGroupRole*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfGroupRole::GetAddr() const { return &Val; }

void FOptionalArrayOfGroupRole::Set(const void* Data)
{
	Val = *((TArray<UGroupRole*>*)Data);
	IsSet = true;
}