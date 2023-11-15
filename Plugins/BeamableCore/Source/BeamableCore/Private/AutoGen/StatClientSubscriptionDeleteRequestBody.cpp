
#include "BeamableCore/Public/AutoGen/StatClientSubscriptionDeleteRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UStatClientSubscriptionDeleteRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("targetGamerTag"), &TargetGamerTag, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("keys"), Keys, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("deleteAll"), &bDeleteAll, Serializer);
}

void UStatClientSubscriptionDeleteRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("targetGamerTag"), &TargetGamerTag, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("keys"), Keys, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("deleteAll"), &bDeleteAll, Serializer);		
}

void UStatClientSubscriptionDeleteRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<int64>(Bag->TryGetField(TEXT("targetGamerTag")), TargetGamerTag, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("keys")), Keys, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("deleteAll", Bag, bDeleteAll, OuterOwner);
}



