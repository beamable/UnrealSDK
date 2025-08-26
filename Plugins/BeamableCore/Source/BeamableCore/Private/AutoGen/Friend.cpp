
#include "BeamableCore/Public/AutoGen/Friend.h"
#include "Serialization/BeamJsonUtils.h"




void UFriend::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("playerId"), &PlayerId, Serializer);
	Serializer->WriteValue(TEXT("source"), UBeamJsonUtils::EnumToSerializationName(Source));
}

void UFriend::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("playerId"), &PlayerId, Serializer);
	Serializer->WriteValue(TEXT("source"), UBeamJsonUtils::EnumToSerializationName(Source));		
}

void UFriend::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(TEXT("playerId"), Bag, PlayerId, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("source"), Bag, Source);
}



