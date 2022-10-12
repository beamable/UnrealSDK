

#include "OptionalArrayOfEventPhaseTimeLibrary.h"

FOptionalArrayOfEventPhaseTime UOptionalArrayOfEventPhaseTimeLibrary::MakeOptionalArrayOfEventPhaseTime(TArray<UEventPhaseTime*> Value)
{
	FOptionalArrayOfEventPhaseTime Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfEventPhaseTime UOptionalArrayOfEventPhaseTimeLibrary::Conv_OptionalArrayOfEventPhaseTimeFromValue(TArray<UEventPhaseTime*> Value)
{
	FOptionalArrayOfEventPhaseTime Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

