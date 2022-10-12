

#include "OptionalClientPermissionLibrary.h"

FOptionalClientPermission UOptionalClientPermissionLibrary::MakeOptionalClientPermission(UClientPermission* Value)
{
	FOptionalClientPermission Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalClientPermission UOptionalClientPermissionLibrary::Conv_OptionalClientPermissionFromValue(UClientPermission* Value)
{
	FOptionalClientPermission Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

