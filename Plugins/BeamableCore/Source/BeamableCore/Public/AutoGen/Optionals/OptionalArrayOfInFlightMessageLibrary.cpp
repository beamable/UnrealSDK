

#include "OptionalArrayOfInFlightMessageLibrary.h"

FOptionalArrayOfInFlightMessage UOptionalArrayOfInFlightMessageLibrary::MakeOptionalArrayOfInFlightMessage(TArray<UInFlightMessage*> Value)
{
	FOptionalArrayOfInFlightMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfInFlightMessage UOptionalArrayOfInFlightMessageLibrary::Conv_OptionalArrayOfInFlightMessageFromValue(TArray<UInFlightMessage*> Value)
{
	FOptionalArrayOfInFlightMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

