

#include "AutoGen/Optionals/OptionalChallengeSolutionLibrary.h"

FOptionalChallengeSolution UOptionalChallengeSolutionLibrary::MakeOptional(UChallengeSolution* Value)
{
	FOptionalChallengeSolution Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalChallengeSolution UOptionalChallengeSolutionLibrary::Conv_OptionalFromValue(UChallengeSolution* Value)
{
	FOptionalChallengeSolution Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalChallengeSolutionLibrary::HasValue(const FOptionalChallengeSolution& Optional, UChallengeSolution*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UChallengeSolution* UOptionalChallengeSolutionLibrary::GetOptionalValue(const FOptionalChallengeSolution& Optional, UChallengeSolution* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

