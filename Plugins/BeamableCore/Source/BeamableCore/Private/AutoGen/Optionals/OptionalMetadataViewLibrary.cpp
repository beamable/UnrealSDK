

#include "AutoGen/Optionals/OptionalMetadataViewLibrary.h"

FOptionalMetadataView UOptionalMetadataViewLibrary::MakeOptional(UMetadataView* Value)
{
	FOptionalMetadataView Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMetadataView UOptionalMetadataViewLibrary::Conv_OptionalFromValue(UMetadataView* Value)
{
	FOptionalMetadataView Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalMetadataViewLibrary::HasValue(const FOptionalMetadataView& Optional, UMetadataView*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UMetadataView* UOptionalMetadataViewLibrary::GetOptionalValue(const FOptionalMetadataView& Optional, UMetadataView* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

