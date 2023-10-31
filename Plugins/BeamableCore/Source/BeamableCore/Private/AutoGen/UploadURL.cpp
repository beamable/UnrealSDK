
#include "BeamableCore/Public/AutoGen/UploadURL.h"





void UUploadURL::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("key"), Key);
	Serializer->WriteValue(TEXT("url"), Url);
}

void UUploadURL::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("key"), Key);
	Serializer->WriteValue(TEXT("url"), Url);		
}

void UUploadURL::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Key = Bag->GetStringField(TEXT("key"));
	Url = Bag->GetStringField(TEXT("url"));
}



