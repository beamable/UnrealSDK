
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfAttachmentProperty.h"

FOptionalArrayOfAttachmentProperty::FOptionalArrayOfAttachmentProperty()
{
	Val = TArray<UAttachmentProperty*>();
	IsSet = false;
}

FOptionalArrayOfAttachmentProperty::FOptionalArrayOfAttachmentProperty(TArray<UAttachmentProperty*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfAttachmentProperty::GetAddr() const { return &Val; }

void FOptionalArrayOfAttachmentProperty::Set(const void* Data)
{
	Val = *((TArray<UAttachmentProperty*>*)Data);
	IsSet = true;
}