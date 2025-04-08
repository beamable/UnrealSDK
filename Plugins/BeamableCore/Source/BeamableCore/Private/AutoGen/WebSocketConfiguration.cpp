
#include "BeamableCore/Public/AutoGen/WebSocketConfiguration.h"
#include "Serialization/BeamJsonUtils.h"




void UWebSocketConfiguration::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("provider"), Provider);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("uri"), &Uri, Serializer);
}

void UWebSocketConfiguration::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("provider"), Provider);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("uri"), &Uri, Serializer);		
}

void UWebSocketConfiguration::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("provider")), Provider);
	UBeamJsonUtils::DeserializeOptional<FString>("uri", Bag, Uri, OuterOwner);
}



