
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamAccountId.h"

FOptionalBeamAccountId::FOptionalBeamAccountId()
{
	Val = FBeamAccountId();
	IsSet = false;
}

FOptionalBeamAccountId::FOptionalBeamAccountId(FBeamAccountId Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamAccountId::GetAddr() const { return &Val; }

void FOptionalBeamAccountId::Set(const void* Data)
{
	Val = *((FBeamAccountId*)Data);
	IsSet = true;
}