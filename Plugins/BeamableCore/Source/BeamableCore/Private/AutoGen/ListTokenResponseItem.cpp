
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("token")), Token);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("platform")), Platform);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("device")), Device);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("created")), Created);
}



