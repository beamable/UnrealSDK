
#include "BeamableCore/Public/AutoGen/ServerEvent.h"
#include "Serialization/BeamJsonUtils.h"




void UServerEvent::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("event"), Event, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("toAll"), bToAll, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("payload"), &Payload, Serializer);
}

void UServerEvent::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("event"), Event, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("toAll"), bToAll, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("payload"), &Payload, Serializer);		
}

void UServerEvent::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("event"), Bag, Event);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("toAll"), Bag, bToAll);
	UBeamJsonUtils::DeserializeOptional<FString>("payload", Bag, Payload, OuterOwner);
}



