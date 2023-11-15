
#include "BeamableCore/Public/AutoGen/StatsClientSubscriptionsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UStatsClientSubscriptionsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UStatsClientSubscriptionsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UStatClientSubscriptionData*>(TEXT("subscriptions"), Subscriptions, Serializer);
}

void UStatsClientSubscriptionsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UStatClientSubscriptionData*>(TEXT("subscriptions"), Subscriptions, Serializer);		
}

void UStatsClientSubscriptionsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UStatClientSubscriptionData*>(Bag->GetArrayField(TEXT("subscriptions")), Subscriptions, OuterOwner);
}



