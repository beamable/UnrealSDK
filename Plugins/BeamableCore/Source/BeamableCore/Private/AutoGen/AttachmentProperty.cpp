
#include "BeamableCore/Public/AutoGen/AttachmentProperty.h"





void UAttachmentProperty::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("value"), Value);
}

void UAttachmentProperty::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("value"), Value);		
}

void UAttachmentProperty::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	Value = Bag->GetStringField(TEXT("value"));
}



