

#include "OptionalMetadataViewLibrary.h"

FOptionalMetadataView UOptionalMetadataViewLibrary::MakeOptionalMetadataView(UMetadataView* Value)
{
	FOptionalMetadataView Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMetadataView UOptionalMetadataViewLibrary::Conv_OptionalMetadataViewFromValue(UMetadataView* Value)
{
	FOptionalMetadataView Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

