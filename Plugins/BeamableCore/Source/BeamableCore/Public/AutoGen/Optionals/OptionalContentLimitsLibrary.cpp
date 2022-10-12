

#include "OptionalContentLimitsLibrary.h"

FOptionalContentLimits UOptionalContentLimitsLibrary::MakeOptionalContentLimits(UContentLimits* Value)
{
	FOptionalContentLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalContentLimits UOptionalContentLimitsLibrary::Conv_OptionalContentLimitsFromValue(UContentLimits* Value)
{
	FOptionalContentLimits Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

