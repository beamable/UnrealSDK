
#include "AutoGen/ServerEvent.h"
#include "Serialization/BeamJsonUtils.h"


void UServerEvent ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("event"), Event);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("payload"), &Payload, Serializer);
	Serializer->WriteValue(TEXT("toAll"), bToAll);
}

void UServerEvent::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("event"), Event);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("payload"), &Payload, Serializer);
	Serializer->WriteValue(TEXT("toAll"), bToAll);		
}

void UServerEvent ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Event = Bag->GetStringField(TEXT("event"));
	UBeamJsonUtils::DeserializeOptional<FString>("payload", Bag, Payload, OuterOwner);
	bToAll = Bag->GetBoolField(TEXT("toAll"));
}