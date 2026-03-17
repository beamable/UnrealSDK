

#include "AutoGen/Optionals/OptionalAuthV2ChallengeSolutionLibrary.h"

FOptionalAuthV2ChallengeSolution UOptionalAuthV2ChallengeSolutionLibrary::MakeOptional(UAuthV2ChallengeSolution* Value)
{
	FOptionalAuthV2ChallengeSolution Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalAuthV2ChallengeSolution UOptionalAuthV2ChallengeSolutionLibrary::Conv_OptionalFromValue(UAuthV2ChallengeSolution* Value)
{
	FOptionalAuthV2ChallengeSolution Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalAuthV2ChallengeSolutionLibrary::HasValue(const FOptionalAuthV2ChallengeSolution& Optional, UAuthV2ChallengeSolution*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UAuthV2ChallengeSolution* UOptionalAuthV2ChallengeSolutionLibrary::GetOptionalValue(const FOptionalAuthV2ChallengeSolution& Optional, UAuthV2ChallengeSolution* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

