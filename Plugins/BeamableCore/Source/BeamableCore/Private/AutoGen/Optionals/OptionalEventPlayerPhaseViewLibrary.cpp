

#include "AutoGen/Optionals/OptionalEventPlayerPhaseViewLibrary.h"

FOptionalEventPlayerPhaseView UOptionalEventPlayerPhaseViewLibrary::MakeOptional(UEventPlayerPhaseView* Value)
{
	FOptionalEventPlayerPhaseView Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalEventPlayerPhaseView UOptionalEventPlayerPhaseViewLibrary::Conv_OptionalFromValue(UEventPlayerPhaseView* Value)
{
	FOptionalEventPlayerPhaseView Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalEventPlayerPhaseViewLibrary::HasValue(const FOptionalEventPlayerPhaseView& Optional, UEventPlayerPhaseView*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UEventPlayerPhaseView* UOptionalEventPlayerPhaseViewLibrary::GetOptionalValue(const FOptionalEventPlayerPhaseView& Optional, UEventPlayerPhaseView* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

