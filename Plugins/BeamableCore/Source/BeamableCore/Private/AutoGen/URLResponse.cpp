
#include "AutoGen/URLResponse.h"



void UURLResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("url"), Url);
	Serializer->WriteValue(TEXT("objectKey"), ObjectKey);
}

void UURLResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("url"), Url);
	Serializer->WriteValue(TEXT("objectKey"), ObjectKey);		
}

void UURLResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Url = Bag->GetStringField(TEXT("url"));
	ObjectKey = Bag->GetStringField(TEXT("objectKey"));
}