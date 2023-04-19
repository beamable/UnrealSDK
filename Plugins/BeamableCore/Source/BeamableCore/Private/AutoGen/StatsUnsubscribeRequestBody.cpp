
#include "BeamableCore/Public/AutoGen/StatsUnsubscribeRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UStatsUnsubscribeRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("service"), Service);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("subscriptions"), &Subscriptions, Serializer);
}

void UStatsUnsubscribeRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("service"), Service);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("subscriptions"), &Subscriptions, Serializer);		
}

void UStatsUnsubscribeRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Service = Bag->GetStringField(TEXT("service"));
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("subscriptions", Bag, Subscriptions, OuterOwner);
}



