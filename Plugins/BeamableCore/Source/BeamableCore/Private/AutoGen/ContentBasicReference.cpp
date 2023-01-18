
#include "AutoGen/ContentBasicReference.h"





void UContentBasicReference ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("contentPrefix"), ContentPrefix);
	Serializer->WriteValue(TEXT("visibility"), Visibility);
	Serializer->WriteValue(TEXT("type"), UContentTypeLibrary::ContentTypeToSerializationName(Type));
}

void UContentBasicReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("contentPrefix"), ContentPrefix);
	Serializer->WriteValue(TEXT("visibility"), Visibility);
	Serializer->WriteValue(TEXT("type"), UContentTypeLibrary::ContentTypeToSerializationName(Type));		
}

void UContentBasicReference ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ContentPrefix = Bag->GetStringField(TEXT("contentPrefix"));
	Visibility = Bag->GetStringField(TEXT("visibility"));
	Type = UContentTypeLibrary::SerializationNameToContentType(Bag->GetStringField(TEXT("type")));
}