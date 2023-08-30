
#include "BeamableCore/Public/AutoGen/Optionals/OptionalPresenceStatus.h"

FOptionalPresenceStatus::FOptionalPresenceStatus()
{
	Val = EPresenceStatus();
	IsSet = false;
}

FOptionalPresenceStatus::FOptionalPresenceStatus(EPresenceStatus Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalPresenceStatus::GetAddr() const { return &Val; }

void FOptionalPresenceStatus::Set(const void* Data)
{
	Val = *((EPresenceStatus*)Data);
	IsSet = true;
}