

#include "OptionalManifestChecksumLibrary.h"

FOptionalManifestChecksum UOptionalManifestChecksumLibrary::MakeOptionalManifestChecksum(UManifestChecksum* Value)
{
	FOptionalManifestChecksum Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalManifestChecksum UOptionalManifestChecksumLibrary::Conv_OptionalManifestChecksumFromValue(UManifestChecksum* Value)
{
	FOptionalManifestChecksum Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

