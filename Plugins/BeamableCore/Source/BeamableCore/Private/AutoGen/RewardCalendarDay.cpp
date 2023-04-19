
#include "BeamableCore/Public/AutoGen/RewardCalendarDay.h"
#include "Serialization/BeamJsonUtils.h"




void URewardCalendarDay::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UEntitlementGenerator*>(TEXT("obtain"), Obtain, Serializer);
}

void URewardCalendarDay::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UEntitlementGenerator*>(TEXT("obtain"), Obtain, Serializer);		
}

void URewardCalendarDay::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UEntitlementGenerator*>(Bag->GetArrayField(TEXT("obtain")), Obtain, OuterOwner);
}



