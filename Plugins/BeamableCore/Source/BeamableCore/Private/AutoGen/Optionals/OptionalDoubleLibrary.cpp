

#include "AutoGen/Optionals/OptionalDoubleLibrary.h"

FOptionalDouble UOptionalDoubleLibrary::MakeOptional(double Value)
{
	FOptionalDouble Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalDouble UOptionalDoubleLibrary::Conv_OptionalFromValue(double Value)
{
	FOptionalDouble Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalDoubleLibrary::HasValue(const FOptionalDouble& Optional, double& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

double UOptionalDoubleLibrary::GetOptionalValue(const FOptionalDouble& Optional, double DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

