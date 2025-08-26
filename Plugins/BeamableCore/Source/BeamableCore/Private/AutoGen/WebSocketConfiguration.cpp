
#include "BeamableCore/Public/AutoGen/WebSocketConfiguration.h"
#include "Serialization/BeamJsonUtils.h"




void UWebSocketConfiguration::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider"), &Provider, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("uri"), &Uri, Serializer);
}

void UWebSocketConfiguration::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider"), &Provider, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("uri"), &Uri, Serializer);		
}

void UWebSocketConfiguration::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("provider", Bag, Provider, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("uri", Bag, Uri, OuterOwner);
}



