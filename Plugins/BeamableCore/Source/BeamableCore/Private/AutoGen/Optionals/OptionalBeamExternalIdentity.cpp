
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamExternalIdentity.h"

FOptionalBeamExternalIdentity::FOptionalBeamExternalIdentity()
{
	Val = FBeamExternalIdentity();
	IsSet = false;
}

FOptionalBeamExternalIdentity::FOptionalBeamExternalIdentity(FBeamExternalIdentity Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamExternalIdentity::GetAddr() const { return &Val; }

void FOptionalBeamExternalIdentity::Set(const void* Data)
{
	Val = *((FBeamExternalIdentity*)Data);
	IsSet = true;
}