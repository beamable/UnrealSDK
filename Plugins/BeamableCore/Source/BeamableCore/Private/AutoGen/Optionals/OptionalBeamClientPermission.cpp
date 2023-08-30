
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamClientPermission.h"

FOptionalBeamClientPermission::FOptionalBeamClientPermission()
{
	Val = FBeamClientPermission();
	IsSet = false;
}

FOptionalBeamClientPermission::FOptionalBeamClientPermission(FBeamClientPermission Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalBeamClientPermission::GetAddr() const { return &Val; }

void FOptionalBeamClientPermission::Set(const void* Data)
{
	Val = *((FBeamClientPermission*)Data);
	IsSet = true;
}