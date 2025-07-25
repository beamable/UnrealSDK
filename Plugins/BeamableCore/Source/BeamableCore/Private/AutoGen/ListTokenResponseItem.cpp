
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
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("token"), Bag, Token);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("platform"), Bag, Platform);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("device"), Bag, Device);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("created"), Bag, Created);
}



