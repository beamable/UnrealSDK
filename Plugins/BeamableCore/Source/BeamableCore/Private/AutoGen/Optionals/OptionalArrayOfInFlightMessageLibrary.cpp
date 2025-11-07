

#include "AutoGen/Optionals/OptionalArrayOfInFlightMessageLibrary.h"

FOptionalArrayOfInFlightMessage UOptionalArrayOfInFlightMessageLibrary::MakeOptional(TArray<UInFlightMessage*> Value)
{
	FOptionalArrayOfInFlightMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfInFlightMessage UOptionalArrayOfInFlightMessageLibrary::Conv_OptionalFromValue(TArray<UInFlightMessage*> Value)
{
	FOptionalArrayOfInFlightMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfInFlightMessageLibrary::HasValue(const FOptionalArrayOfInFlightMessage& Optional, TArray<UInFlightMessage*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UInFlightMessage*> UOptionalArrayOfInFlightMessageLibrary::GetOptionalValue(const FOptionalArrayOfInFlightMessage& Optional, TArray<UInFlightMessage*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

