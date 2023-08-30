

#include "AutoGen/Optionals/OptionalMapOfDoubleLibrary.h"

FOptionalMapOfDouble UOptionalMapOfDoubleLibrary::MakeOptional(TMap<FString, double> Value)
{
	FOptionalMapOfDouble Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMapOfDouble UOptionalMapOfDoubleLibrary::Conv_OptionalFromValue(TMap<FString, double> Value)
{
	FOptionalMapOfDouble Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalMapOfDoubleLibrary::HasValue(const FOptionalMapOfDouble& Optional, TMap<FString, double>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TMap<FString, double> UOptionalMapOfDoubleLibrary::GetOptionalValue(const FOptionalMapOfDouble& Optional, TMap<FString, double> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

