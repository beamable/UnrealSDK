
#include "BeamableCore/Public/AutoGen/ListTokenResponseItem.h"





void UListTokenResponseItem::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("token"), Token);
	Serializer->WriteValue(TEXT("platform"), Platform);
	Serializer->WriteValue(TEXT("device"), Device);
	Serializer->WriteValue(TEXT("created"), Created);
}

void UListTokenResponseItem::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("token"), Token);
	Serializer->WriteValue(TEXT("platform"), Platform);
	Serializer->WriteValue(TEXT("device"), Device);
	Serializer->WriteValue(TEXT("created"), Created);		
}

void UListTokenResponseItem::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Token = Bag->GetStringField(TEXT("token"));
	Platform = Bag->GetStringField(TEXT("platform"));
	Device = Bag->GetStringField(TEXT("device"));
	Created = Bag->GetStringField(TEXT("created"));
}



