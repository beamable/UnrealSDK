

#include "AutoGen/Optionals/OptionalContentTagFilterLibrary.h"

FOptionalContentTagFilter UOptionalContentTagFilterLibrary::MakeOptional(UContentTagFilter* Value)
{
	FOptionalContentTagFilter Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalContentTagFilter UOptionalContentTagFilterLibrary::Conv_OptionalFromValue(UContentTagFilter* Value)
{
	FOptionalContentTagFilter Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalContentTagFilterLibrary::HasValue(const FOptionalContentTagFilter& Optional, UContentTagFilter*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UContentTagFilter* UOptionalContentTagFilterLibrary::GetOptionalValue(const FOptionalContentTagFilter& Optional, UContentTagFilter* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

