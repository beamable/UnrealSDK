
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
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("event")), Event);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("toAll")), bToAll);
	UBeamJsonUtils::DeserializeOptional<FString>("payload", Bag, Payload, OuterOwner);
}



