

#include "AutoGen/Optionals/OptionalClientPermissionLibrary.h"

FOptionalClientPermission UOptionalClientPermissionLibrary::MakeOptional(UClientPermission* Value)
{
	FOptionalClientPermission Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalClientPermission UOptionalClientPermissionLibrary::Conv_OptionalFromValue(UClientPermission* Value)
{
	FOptionalClientPermission Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalClientPermissionLibrary::HasValue(const FOptionalClientPermission& Optional, UClientPermission*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UClientPermission* UOptionalClientPermissionLibrary::GetOptionalValue(const FOptionalClientPermission& Optional, UClientPermission* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

