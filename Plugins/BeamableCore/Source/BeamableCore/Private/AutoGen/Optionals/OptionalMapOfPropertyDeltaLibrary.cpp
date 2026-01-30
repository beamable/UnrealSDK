

#include "AutoGen/Optionals/OptionalMapOfPropertyDeltaLibrary.h"

FOptionalMapOfPropertyDelta UOptionalMapOfPropertyDeltaLibrary::MakeOptional(TMap<FString, UPropertyDelta*> Value)
{
	FOptionalMapOfPropertyDelta Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMapOfPropertyDelta UOptionalMapOfPropertyDeltaLibrary::Conv_OptionalFromValue(TMap<FString, UPropertyDelta*> Value)
{
	FOptionalMapOfPropertyDelta Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalMapOfPropertyDeltaLibrary::HasValue(const FOptionalMapOfPropertyDelta& Optional, TMap<FString, UPropertyDelta*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TMap<FString, UPropertyDelta*> UOptionalMapOfPropertyDeltaLibrary::GetOptionalValue(const FOptionalMapOfPropertyDelta& Optional, TMap<FString, UPropertyDelta*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

