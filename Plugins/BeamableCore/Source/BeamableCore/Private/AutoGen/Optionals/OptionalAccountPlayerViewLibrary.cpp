

#include "AutoGen/Optionals/OptionalAccountPlayerViewLibrary.h"

FOptionalAccountPlayerView UOptionalAccountPlayerViewLibrary::MakeOptional(UAccountPlayerView* Value)
{
	FOptionalAccountPlayerView Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalAccountPlayerView UOptionalAccountPlayerViewLibrary::Conv_OptionalFromValue(UAccountPlayerView* Value)
{
	FOptionalAccountPlayerView Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalAccountPlayerViewLibrary::HasValue(const FOptionalAccountPlayerView& Optional, UAccountPlayerView*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UAccountPlayerView* UOptionalAccountPlayerViewLibrary::GetOptionalValue(const FOptionalAccountPlayerView& Optional, UAccountPlayerView* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

