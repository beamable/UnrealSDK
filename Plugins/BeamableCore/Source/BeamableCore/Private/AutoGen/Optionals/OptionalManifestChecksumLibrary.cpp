

#include "AutoGen/Optionals/OptionalManifestChecksumLibrary.h"

FOptionalManifestChecksum UOptionalManifestChecksumLibrary::MakeOptional(UManifestChecksum* Value)
{
	FOptionalManifestChecksum Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalManifestChecksum UOptionalManifestChecksumLibrary::Conv_OptionalFromValue(UManifestChecksum* Value)
{
	FOptionalManifestChecksum Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalManifestChecksumLibrary::HasValue(const FOptionalManifestChecksum& Optional, UManifestChecksum*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UManifestChecksum* UOptionalManifestChecksumLibrary::GetOptionalValue(const FOptionalManifestChecksum& Optional, UManifestChecksum* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

