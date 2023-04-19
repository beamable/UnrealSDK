
#include "BeamableCore/Public/AutoGen/StatsSubscribeRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UStatsSubscribeRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("service"), Service);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("subscriptions"), Subscriptions, Serializer);
}

void UStatsSubscribeRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("service"), Service);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("subscriptions"), Subscriptions, Serializer);		
}

void UStatsSubscribeRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Service = Bag->GetStringField(TEXT("service"));
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("subscriptions")), Subscriptions, OuterOwner);
}



