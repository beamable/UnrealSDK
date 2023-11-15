
#include "BeamableCore/Public/AutoGen/StatClientSubscriptionRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UStatClientSubscriptionRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("targetGamerTag"), &TargetGamerTag, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("keys"), Keys, Serializer);
}

void UStatClientSubscriptionRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("targetGamerTag"), &TargetGamerTag, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("keys"), Keys, Serializer);		
}

void UStatClientSubscriptionRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<int64>(Bag->TryGetField(TEXT("targetGamerTag")), TargetGamerTag, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("keys")), Keys, OuterOwner);
}



