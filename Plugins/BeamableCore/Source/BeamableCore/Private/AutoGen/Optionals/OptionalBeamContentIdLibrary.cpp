

#include "AutoGen/Optionals/OptionalBeamContentIdLibrary.h"

FOptionalBeamContentId UOptionalBeamContentIdLibrary::MakeOptional(FBeamContentId Value)
{
	FOptionalBeamContentId Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamContentId UOptionalBeamContentIdLibrary::Conv_OptionalFromValue(FBeamContentId Value)
{
	FOptionalBeamContentId Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamContentIdLibrary::HasValue(const FOptionalBeamContentId& Optional, FBeamContentId& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

FBeamContentId UOptionalBeamContentIdLibrary::GetOptionalValue(const FOptionalBeamContentId& Optional, FBeamContentId DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

