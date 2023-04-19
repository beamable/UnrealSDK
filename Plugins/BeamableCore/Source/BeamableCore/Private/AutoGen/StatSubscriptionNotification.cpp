
#include "BeamableCore/Public/AutoGen/StatSubscriptionNotification.h"
#include "Serialization/BeamJsonUtils.h"




void UStatSubscriptionNotification::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<FString>(TEXT("statsBefore"), StatsBefore, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("statsAfter"), StatsAfter, Serializer);
}

void UStatSubscriptionNotification::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeMap<FString>(TEXT("statsBefore"), StatsBefore, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("statsAfter"), StatsAfter, Serializer);		
}

void UStatSubscriptionNotification::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("statsBefore")), StatsBefore, OuterOwner);
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("statsAfter")), StatsAfter, OuterOwner);
}



