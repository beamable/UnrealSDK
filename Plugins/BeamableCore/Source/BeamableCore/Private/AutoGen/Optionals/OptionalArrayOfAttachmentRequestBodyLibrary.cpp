

#include "AutoGen/Optionals/OptionalArrayOfAttachmentRequestBodyLibrary.h"

FOptionalArrayOfAttachmentRequestBody UOptionalArrayOfAttachmentRequestBodyLibrary::MakeOptional(TArray<UAttachmentRequestBody*> Value)
{
	FOptionalArrayOfAttachmentRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfAttachmentRequestBody UOptionalArrayOfAttachmentRequestBodyLibrary::Conv_OptionalFromValue(TArray<UAttachmentRequestBody*> Value)
{
	FOptionalArrayOfAttachmentRequestBody Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfAttachmentRequestBodyLibrary::HasValue(const FOptionalArrayOfAttachmentRequestBody& Optional, TArray<UAttachmentRequestBody*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UAttachmentRequestBody*> UOptionalArrayOfAttachmentRequestBodyLibrary::GetOptionalValue(const FOptionalArrayOfAttachmentRequestBody& Optional, TArray<UAttachmentRequestBody*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

