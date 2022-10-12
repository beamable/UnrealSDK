

#include "OptionalEventPhaseRuntimeLibrary.h"

FOptionalEventPhaseRuntime UOptionalEventPhaseRuntimeLibrary::MakeOptionalEventPhaseRuntime(UEventPhaseRuntime* Value)
{
	FOptionalEventPhaseRuntime Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalEventPhaseRuntime UOptionalEventPhaseRuntimeLibrary::Conv_OptionalEventPhaseRuntimeFromValue(UEventPhaseRuntime* Value)
{
	FOptionalEventPhaseRuntime Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

