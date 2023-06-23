

#include "AutoGen/Optionals/OptionalBeamClientPermissionLibrary.h"

FOptionalBeamClientPermission UOptionalBeamClientPermissionLibrary::MakeOptional(FBeamClientPermission Value)
{
	FOptionalBeamClientPermission Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamClientPermission UOptionalBeamClientPermissionLibrary::Conv_OptionalFromValue(FBeamClientPermission Value)
{
	FOptionalBeamClientPermission Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamClientPermissionLibrary::HasValue(const FOptionalBeamClientPermission& Optional, FBeamClientPermission& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

FBeamClientPermission UOptionalBeamClientPermissionLibrary::GetOptionalValue(const FOptionalBeamClientPermission& Optional, FBeamClientPermission DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

