

#include "OptionalArrayOfAttachmentRequestBodyLibrary.h"

FOptionalArrayOfAttachmentRequestBody UOptionalArrayOfAttachmentRequestBodyLibrary::MakeOptionalArrayOfAttachmentRequestBody(TArray<UAttachmentRequestBody*> Value)
{
	FOptionalArrayOfAttachmentRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfAttachmentRequestBody UOptionalArrayOfAttachmentRequestBodyLibrary::Conv_OptionalArrayOfAttachmentRequestBodyFromValue(TArray<UAttachmentRequestBody*> Value)
{
	FOptionalArrayOfAttachmentRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

