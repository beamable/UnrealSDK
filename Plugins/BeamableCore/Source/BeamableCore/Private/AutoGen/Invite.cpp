
#include "BeamableCore/Public/AutoGen/Invite.h"
#include "Serialization/BeamJsonUtils.h"




void UInvite::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("playerId"), &PlayerId, Serializer);
	Serializer->WriteValue(TEXT("direction"), UBeamJsonUtils::EnumToSerializationName(Direction));
}

void UInvite::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("playerId"), &PlayerId, Serializer);
	Serializer->WriteValue(TEXT("direction"), UBeamJsonUtils::EnumToSerializationName(Direction));		
}

void UInvite::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(TEXT("playerId"), Bag, PlayerId, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("direction"), Bag, Direction);
}



