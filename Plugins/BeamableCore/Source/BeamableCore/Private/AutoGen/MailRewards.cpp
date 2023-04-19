
#include "BeamableCore/Public/AutoGen/MailRewards.h"
#include "Serialization/BeamJsonUtils.h"




void UMailRewards::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UCurrencyChange*>(TEXT("currencies"), Currencies, Serializer);
	UBeamJsonUtils::SerializeArray<UItemCreateRequestBody*>(TEXT("items"), Items, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("applyVipBonus"), &bApplyVipBonus, Serializer);
}

void UMailRewards::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UCurrencyChange*>(TEXT("currencies"), Currencies, Serializer);
	UBeamJsonUtils::SerializeArray<UItemCreateRequestBody*>(TEXT("items"), Items, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("applyVipBonus"), &bApplyVipBonus, Serializer);		
}

void UMailRewards::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UCurrencyChange*>(Bag->GetArrayField(TEXT("currencies")), Currencies, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UItemCreateRequestBody*>(Bag->GetArrayField(TEXT("items")), Items, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("applyVipBonus", Bag, bApplyVipBonus, OuterOwner);
}



