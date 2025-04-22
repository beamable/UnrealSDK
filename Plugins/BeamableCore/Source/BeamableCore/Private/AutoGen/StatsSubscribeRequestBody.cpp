
#include "BeamableCore/Public/AutoGen/StatsSubscribeRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UStatsSubscribeRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("service"), Service, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("subscriptions"), Subscriptions, Serializer);
}

void UStatsSubscribeRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("service"), Service, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("subscriptions"), Subscriptions, Serializer);		
}

void UStatsSubscribeRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("service")), Service);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("subscriptions")), Subscriptions, OuterOwner);
}



