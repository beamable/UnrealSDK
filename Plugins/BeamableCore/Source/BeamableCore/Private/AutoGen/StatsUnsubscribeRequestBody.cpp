
#include "BeamableCore/Public/AutoGen/StatsUnsubscribeRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UStatsUnsubscribeRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("service"), Service, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("subscriptions"), &Subscriptions, Serializer);
}

void UStatsUnsubscribeRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("service"), Service, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("subscriptions"), &Subscriptions, Serializer);		
}

void UStatsUnsubscribeRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("service")), Service);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("subscriptions", Bag, Subscriptions, OuterOwner);
}



