

#include "OptionalContextInfoLibrary.h"

FOptionalContextInfo UOptionalContextInfoLibrary::MakeOptionalContextInfo(UContextInfo* Value)
{
	FOptionalContextInfo Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalContextInfo UOptionalContextInfoLibrary::Conv_OptionalContextInfoFromValue(UContextInfo* Value)
{
	FOptionalContextInfo Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

