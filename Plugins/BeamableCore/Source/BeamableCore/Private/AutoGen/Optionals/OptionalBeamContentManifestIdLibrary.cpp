

#include "AutoGen/Optionals/OptionalBeamContentManifestIdLibrary.h"

FOptionalBeamContentManifestId UOptionalBeamContentManifestIdLibrary::MakeOptional(FBeamContentManifestId Value)
{
	FOptionalBeamContentManifestId Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamContentManifestId UOptionalBeamContentManifestIdLibrary::Conv_OptionalFromValue(FBeamContentManifestId Value)
{
	FOptionalBeamContentManifestId Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamContentManifestIdLibrary::HasValue(const FOptionalBeamContentManifestId& Optional, FBeamContentManifestId& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

FBeamContentManifestId UOptionalBeamContentManifestIdLibrary::GetOptionalValue(const FOptionalBeamContentManifestId& Optional, FBeamContentManifestId DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

