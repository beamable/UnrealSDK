

#include "OptionalEventPlayerPhaseViewLibrary.h"

FOptionalEventPlayerPhaseView UOptionalEventPlayerPhaseViewLibrary::MakeOptionalEventPlayerPhaseView(UEventPlayerPhaseView* Value)
{
	FOptionalEventPlayerPhaseView Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalEventPlayerPhaseView UOptionalEventPlayerPhaseViewLibrary::Conv_OptionalEventPlayerPhaseViewFromValue(UEventPlayerPhaseView* Value)
{
	FOptionalEventPlayerPhaseView Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

