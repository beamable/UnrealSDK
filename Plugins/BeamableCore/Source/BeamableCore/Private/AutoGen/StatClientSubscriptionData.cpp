
#include "BeamableCore/Public/AutoGen/StatClientSubscriptionData.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UStatClientSubscriptionData::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("targetGamerTag"), TargetGamerTag);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("keys"), Keys, Serializer);
}

void UStatClientSubscriptionData::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("targetGamerTag"), TargetGamerTag);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("keys"), Keys, Serializer);		
}

void UStatClientSubscriptionData::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("targetGamerTag")), TargetGamerTag);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("keys")), Keys, OuterOwner);
}



