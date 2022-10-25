

#include "AutoGen/Optionals/OptionalLeaderboardCohortSettingsLibrary.h"

FOptionalLeaderboardCohortSettings UOptionalLeaderboardCohortSettingsLibrary::MakeOptional(ULeaderboardCohortSettings* Value)
{
	FOptionalLeaderboardCohortSettings Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalLeaderboardCohortSettings UOptionalLeaderboardCohortSettingsLibrary::Conv_OptionalFromValue(ULeaderboardCohortSettings* Value)
{
	FOptionalLeaderboardCohortSettings Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalLeaderboardCohortSettingsLibrary::HasValue(const FOptionalLeaderboardCohortSettings& Optional, ULeaderboardCohortSettings*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

ULeaderboardCohortSettings* UOptionalLeaderboardCohortSettingsLibrary::GetOptionalValue(const FOptionalLeaderboardCohortSettings& Optional, ULeaderboardCohortSettings* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

