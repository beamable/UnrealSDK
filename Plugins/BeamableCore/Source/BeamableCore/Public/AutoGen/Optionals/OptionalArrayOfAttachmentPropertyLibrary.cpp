

#include "OptionalArrayOfAttachmentPropertyLibrary.h"

FOptionalArrayOfAttachmentProperty UOptionalArrayOfAttachmentPropertyLibrary::MakeOptionalArrayOfAttachmentProperty(TArray<UAttachmentProperty*> Value)
{
	FOptionalArrayOfAttachmentProperty Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfAttachmentProperty UOptionalArrayOfAttachmentPropertyLibrary::Conv_OptionalArrayOfAttachmentPropertyFromValue(TArray<UAttachmentProperty*> Value)
{
	FOptionalArrayOfAttachmentProperty Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

