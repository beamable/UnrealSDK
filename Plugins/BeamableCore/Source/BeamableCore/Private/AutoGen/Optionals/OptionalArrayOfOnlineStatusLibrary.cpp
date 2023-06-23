

#include "AutoGen/Optionals/OptionalArrayOfOnlineStatusLibrary.h"

FOptionalArrayOfOnlineStatus UOptionalArrayOfOnlineStatusLibrary::MakeOptional(TArray<UOnlineStatus*> Value)
{
	FOptionalArrayOfOnlineStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfOnlineStatus UOptionalArrayOfOnlineStatusLibrary::Conv_OptionalFromValue(TArray<UOnlineStatus*> Value)
{
	FOptionalArrayOfOnlineStatus Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfOnlineStatusLibrary::HasValue(const FOptionalArrayOfOnlineStatus& Optional, TArray<UOnlineStatus*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UOnlineStatus*> UOptionalArrayOfOnlineStatusLibrary::GetOptionalValue(const FOptionalArrayOfOnlineStatus& Optional, TArray<UOnlineStatus*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

