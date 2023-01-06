

#include "AutoGen/Optionals/OptionalBeamStatsTypeLibrary.h"

FOptionalBeamStatsType UOptionalBeamStatsTypeLibrary::MakeOptional(FBeamStatsType Value)
{
	FOptionalBeamStatsType Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamStatsType UOptionalBeamStatsTypeLibrary::Conv_OptionalFromValue(FBeamStatsType Value)
{
	FOptionalBeamStatsType Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamStatsTypeLibrary::HasValue(const FOptionalBeamStatsType& Optional, FBeamStatsType& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

FBeamStatsType UOptionalBeamStatsTypeLibrary::GetOptionalValue(const FOptionalBeamStatsType& Optional, FBeamStatsType DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

