

#include "AutoGen/Optionals/OptionalArrayOfAttachmentPropertyLibrary.h"

FOptionalArrayOfAttachmentProperty UOptionalArrayOfAttachmentPropertyLibrary::MakeOptional(TArray<UAttachmentProperty*> Value)
{
	FOptionalArrayOfAttachmentProperty Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfAttachmentProperty UOptionalArrayOfAttachmentPropertyLibrary::Conv_OptionalFromValue(TArray<UAttachmentProperty*> Value)
{
	FOptionalArrayOfAttachmentProperty Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfAttachmentPropertyLibrary::HasValue(const FOptionalArrayOfAttachmentProperty& Optional, TArray<UAttachmentProperty*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UAttachmentProperty*> UOptionalArrayOfAttachmentPropertyLibrary::GetOptionalValue(const FOptionalArrayOfAttachmentProperty& Optional, TArray<UAttachmentProperty*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

