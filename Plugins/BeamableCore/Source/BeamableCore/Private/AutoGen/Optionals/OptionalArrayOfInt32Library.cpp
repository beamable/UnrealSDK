

#include "AutoGen/Optionals/OptionalArrayOfInt32Library.h"

FOptionalArrayOfInt32 UOptionalArrayOfInt32Library::MakeOptional(TArray<int32> Value)
{
	FOptionalArrayOfInt32 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfInt32 UOptionalArrayOfInt32Library::Conv_OptionalFromValue(TArray<int32> Value)
{
	FOptionalArrayOfInt32 Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfInt32Library::HasValue(const FOptionalArrayOfInt32& Optional, TArray<int32>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<int32> UOptionalArrayOfInt32Library::GetOptionalValue(const FOptionalArrayOfInt32& Optional, TArray<int32> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

