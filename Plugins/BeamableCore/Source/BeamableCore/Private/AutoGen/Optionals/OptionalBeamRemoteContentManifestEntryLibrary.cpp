

#include "AutoGen/Optionals/OptionalBeamRemoteContentManifestEntryLibrary.h"

FOptionalBeamRemoteContentManifestEntry UOptionalBeamRemoteContentManifestEntryLibrary::MakeOptional(FBeamRemoteContentManifestEntry Value)
{
	FOptionalBeamRemoteContentManifestEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamRemoteContentManifestEntry UOptionalBeamRemoteContentManifestEntryLibrary::Conv_OptionalFromValue(FBeamRemoteContentManifestEntry Value)
{
	FOptionalBeamRemoteContentManifestEntry Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamRemoteContentManifestEntryLibrary::HasValue(const FOptionalBeamRemoteContentManifestEntry& Optional, FBeamRemoteContentManifestEntry& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

FBeamRemoteContentManifestEntry UOptionalBeamRemoteContentManifestEntryLibrary::GetOptionalValue(const FOptionalBeamRemoteContentManifestEntry& Optional, FBeamRemoteContentManifestEntry DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

