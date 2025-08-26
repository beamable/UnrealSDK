
#include "BeamableCore/Public/AutoGen/PromotionScope.h"
#include "Serialization/BeamJsonUtils.h"




void UPromotionScope::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), UBeamJsonUtils::EnumToSerializationName(Name));
	UBeamJsonUtils::SerializeOptional<TArray<UPromotion*>, UPromotion*>(TEXT("promotions"), &Promotions, Serializer);
}

void UPromotionScope::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), UBeamJsonUtils::EnumToSerializationName(Name));
	UBeamJsonUtils::SerializeOptional<TArray<UPromotion*>, UPromotion*>(TEXT("promotions"), &Promotions, Serializer);		
}

void UPromotionScope::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeOptional<TArray<UPromotion*>, UPromotion*>("promotions", Bag, Promotions, OuterOwner);
}



