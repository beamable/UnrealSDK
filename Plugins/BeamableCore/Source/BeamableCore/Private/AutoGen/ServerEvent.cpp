
#include "BeamableCore/Public/AutoGen/ServerEvent.h"
#include "Serialization/BeamJsonUtils.h"




void UServerEvent::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("event"), Event);
	Serializer->WriteValue(TEXT("toAll"), bToAll);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("payload"), &Payload, Serializer);
}

void UServerEvent::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("event"), Event);
	Serializer->WriteValue(TEXT("toAll"), bToAll);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("payload"), &Payload, Serializer);		
}

void UServerEvent::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Event = Bag->GetStringField(TEXT("event"));
	bToAll = Bag->GetBoolField(TEXT("toAll"));
	UBeamJsonUtils::DeserializeOptional<FString>("payload", Bag, Payload, OuterOwner);
}



