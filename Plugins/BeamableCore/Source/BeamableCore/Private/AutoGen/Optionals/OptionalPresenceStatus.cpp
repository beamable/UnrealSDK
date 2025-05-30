
#include "BeamableCore/Public/AutoGen/Optionals/OptionalPresenceStatus.h"

FOptionalPresenceStatus::FOptionalPresenceStatus()
{
	Val = EBeamPresenceStatus();
	IsSet = false;
}

FOptionalPresenceStatus::FOptionalPresenceStatus(EBeamPresenceStatus Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalPresenceStatus::GetAddr() const { return &Val; }

void FOptionalPresenceStatus::Set(const void* Data)
{
	Val = *((EBeamPresenceStatus*)Data);
	IsSet = true;
}