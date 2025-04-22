
#include "BeamableCore/Public/AutoGen/ListTokenResponseItem.h"





void UListTokenResponseItem::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("token"), Token, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("platform"), Platform, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("device"), Device, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);
}

void UListTokenResponseItem::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("token"), Token, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("platform"), Platform, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("device"), Device, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);		
}

void UListTokenResponseItem::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("token")), Token);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("platform")), Platform);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("device")), Device);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("created")), Created);
}



