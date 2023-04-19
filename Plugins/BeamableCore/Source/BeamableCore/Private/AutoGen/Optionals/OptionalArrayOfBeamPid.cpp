
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamPid.h"

FOptionalArrayOfBeamPid::FOptionalArrayOfBeamPid()
{
	Val = TArray<FBeamPid>();
	IsSet = false;
}

FOptionalArrayOfBeamPid::FOptionalArrayOfBeamPid(TArray<FBeamPid> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfBeamPid::GetAddr() const { return &Val; }

void FOptionalArrayOfBeamPid::Set(const void* Data)
{
	Val = *((TArray<FBeamPid>*)Data);
	IsSet = true;
}