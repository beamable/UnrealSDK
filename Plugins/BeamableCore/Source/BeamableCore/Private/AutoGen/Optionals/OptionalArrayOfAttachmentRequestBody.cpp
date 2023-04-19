
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfAttachmentRequestBody.h"

FOptionalArrayOfAttachmentRequestBody::FOptionalArrayOfAttachmentRequestBody()
{
	Val = TArray<UAttachmentRequestBody*>();
	IsSet = false;
}

FOptionalArrayOfAttachmentRequestBody::FOptionalArrayOfAttachmentRequestBody(TArray<UAttachmentRequestBody*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfAttachmentRequestBody::GetAddr() const { return &Val; }

void FOptionalArrayOfAttachmentRequestBody::Set(const void* Data)
{
	Val = *((TArray<UAttachmentRequestBody*>*)Data);
	IsSet = true;
}