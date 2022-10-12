

#include "OptionalLeaderboardCohortSettingsLibrary.h"

FOptionalLeaderboardCohortSettings UOptionalLeaderboardCohortSettingsLibrary::MakeOptionalLeaderboardCohortSettings(ULeaderboardCohortSettings* Value)
{
	FOptionalLeaderboardCohortSettings Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalLeaderboardCohortSettings UOptionalLeaderboardCohortSettingsLibrary::Conv_OptionalLeaderboardCohortSettingsFromValue(ULeaderboardCohortSettings* Value)
{
	FOptionalLeaderboardCohortSettings Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

