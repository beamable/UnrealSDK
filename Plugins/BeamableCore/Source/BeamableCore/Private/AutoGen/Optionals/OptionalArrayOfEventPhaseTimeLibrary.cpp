

#include "AutoGen/Optionals/OptionalArrayOfEventPhaseTimeLibrary.h"

FOptionalArrayOfEventPhaseTime UOptionalArrayOfEventPhaseTimeLibrary::MakeOptional(TArray<UEventPhaseTime*> Value)
{
	FOptionalArrayOfEventPhaseTime Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfEventPhaseTime UOptionalArrayOfEventPhaseTimeLibrary::Conv_OptionalFromValue(TArray<UEventPhaseTime*> Value)
{
	FOptionalArrayOfEventPhaseTime Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfEventPhaseTimeLibrary::HasValue(const FOptionalArrayOfEventPhaseTime& Optional, TArray<UEventPhaseTime*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UEventPhaseTime*> UOptionalArrayOfEventPhaseTimeLibrary::GetOptionalValue(const FOptionalArrayOfEventPhaseTime& Optional, TArray<UEventPhaseTime*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

