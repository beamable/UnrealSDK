
#include "AutoGen/SendMessageResponse.h"
#include "Serialization/BeamJsonUtils.h"


void USendMessageResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UChatV2ObjectMessage*>("message", Message, Serializer);
}

void USendMessageResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UChatV2ObjectMessage*>("message", Message, Serializer);		
}

void USendMessageResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UChatV2ObjectMessage*>("message", Bag, Message, OuterOwner);
}