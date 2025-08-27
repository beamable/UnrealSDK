
#include "BeamableCore/Public/AutoGen/PromotionScope.h"
#include "Serialization/BeamJsonUtils.h"




void UPromotionScope::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeArray<UPromotion*>(TEXT("promotions"), Promotions, Serializer);
}

void UPromotionScope::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeArray<UPromotion*>(TEXT("promotions"), Promotions, Serializer);		
}

void UPromotionScope::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeArray<UPromotion*>(TEXT("promotions"), Bag, Promotions, OuterOwner);
}



