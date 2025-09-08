

#include "AutoGen/Optionals/OptionalArrayOfEventsBasicInFlightMessageLibrary.h"

FOptionalArrayOfEventsBasicInFlightMessage UOptionalArrayOfEventsBasicInFlightMessageLibrary::MakeOptional(TArray<UEventsBasicInFlightMessage*> Value)
{
	FOptionalArrayOfEventsBasicInFlightMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfEventsBasicInFlightMessage UOptionalArrayOfEventsBasicInFlightMessageLibrary::Conv_OptionalFromValue(TArray<UEventsBasicInFlightMessage*> Value)
{
	FOptionalArrayOfEventsBasicInFlightMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfEventsBasicInFlightMessageLibrary::HasValue(const FOptionalArrayOfEventsBasicInFlightMessage& Optional, TArray<UEventsBasicInFlightMessage*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UEventsBasicInFlightMessage*> UOptionalArrayOfEventsBasicInFlightMessageLibrary::GetOptionalValue(const FOptionalArrayOfEventsBasicInFlightMessage& Optional, TArray<UEventsBasicInFlightMessage*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

