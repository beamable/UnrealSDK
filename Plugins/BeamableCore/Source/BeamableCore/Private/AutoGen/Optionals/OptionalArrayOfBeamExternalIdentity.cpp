
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamExternalIdentity.h"

FOptionalArrayOfBeamExternalIdentity::FOptionalArrayOfBeamExternalIdentity()
{
	Val = TArray<FBeamExternalIdentity>();
	IsSet = false;
}

FOptionalArrayOfBeamExternalIdentity::FOptionalArrayOfBeamExternalIdentity(TArray<FBeamExternalIdentity> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamExternalIdentity::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamExternalIdentity::Set(const void* Data)
{
	Val = *((TArray<FBeamExternalIdentity>*)Data);
	IsSet = true;
}