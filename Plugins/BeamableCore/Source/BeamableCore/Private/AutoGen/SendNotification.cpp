
#include "BeamableCore/Public/AutoGen/SendNotification.h"
#include "Serialization/BeamJsonUtils.h"




void USendNotification::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("title"), &Title, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);
}

void USendNotification::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("title"), &Title, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("body"), &Body, Serializer);		
}

void USendNotification::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("title", Bag, Title, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("body", Bag, Body, OuterOwner);
}



