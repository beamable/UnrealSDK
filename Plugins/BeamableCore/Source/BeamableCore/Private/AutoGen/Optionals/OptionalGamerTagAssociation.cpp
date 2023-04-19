
#include "BeamableCore/Public/AutoGen/Optionals/OptionalGamerTagAssociation.h"

FOptionalGamerTagAssociation::FOptionalGamerTagAssociation()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalGamerTagAssociation::FOptionalGamerTagAssociation(UGamerTagAssociation* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalGamerTagAssociation::GetAddr() const { return &Val; }

void FOptionalGamerTagAssociation::Set(const void* Data)
{
	Val = *((UGamerTagAssociation**)Data);
	IsSet = true;
}