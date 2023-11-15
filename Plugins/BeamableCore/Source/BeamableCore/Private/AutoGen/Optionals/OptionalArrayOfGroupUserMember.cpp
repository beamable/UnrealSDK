
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfGroupUserMember.h"

FOptionalArrayOfGroupUserMember::FOptionalArrayOfGroupUserMember()
{
	Val = TArray<UGroupUserMember*>();
	IsSet = false;
}

FOptionalArrayOfGroupUserMember::FOptionalArrayOfGroupUserMember(TArray<UGroupUserMember*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfGroupUserMember::GetAddr() const { return &Val; }

void FOptionalArrayOfGroupUserMember::Set(const void* Data)
{
	Val = *((TArray<UGroupUserMember*>*)Data);
	IsSet = true;
}