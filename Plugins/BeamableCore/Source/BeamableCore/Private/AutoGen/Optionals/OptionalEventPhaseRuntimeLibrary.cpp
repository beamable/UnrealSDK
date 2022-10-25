

#include "AutoGen/Optionals/OptionalEventPhaseRuntimeLibrary.h"

FOptionalEventPhaseRuntime UOptionalEventPhaseRuntimeLibrary::MakeOptional(UEventPhaseRuntime* Value)
{
	FOptionalEventPhaseRuntime Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalEventPhaseRuntime UOptionalEventPhaseRuntimeLibrary::Conv_OptionalFromValue(UEventPhaseRuntime* Value)
{
	FOptionalEventPhaseRuntime Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalEventPhaseRuntimeLibrary::HasValue(const FOptionalEventPhaseRuntime& Optional, UEventPhaseRuntime*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UEventPhaseRuntime* UOptionalEventPhaseRuntimeLibrary::GetOptionalValue(const FOptionalEventPhaseRuntime& Optional, UEventPhaseRuntime* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

