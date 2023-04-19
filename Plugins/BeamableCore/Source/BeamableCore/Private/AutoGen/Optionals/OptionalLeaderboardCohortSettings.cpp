
#include "BeamableCore/Public/AutoGen/Optionals/OptionalLeaderboardCohortSettings.h"

FOptionalLeaderboardCohortSettings::FOptionalLeaderboardCohortSettings()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalLeaderboardCohortSettings::FOptionalLeaderboardCohortSettings(ULeaderboardCohortSettings* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalLeaderboardCohortSettings::GetAddr() const { return &Val; }

void FOptionalLeaderboardCohortSettings::Set(const void* Data)
{
	Val = *((ULeaderboardCohortSettings**)Data);
	IsSet = true;
}