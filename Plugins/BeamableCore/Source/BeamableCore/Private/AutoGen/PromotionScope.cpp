
#include "BeamableCore/Public/AutoGen/PromotionScope.h"
#include "Serialization/BeamJsonUtils.h"




void UPromotionScope::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeArray<UPromotion*>(TEXT("promotions"), Promotions, Serializer);
}

void UPromotionScope::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeArray<UPromotion*>(TEXT("promotions"), Promotions, Serializer);		
}

void UPromotionScope::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), Name);
	UBeamJsonUtils::DeserializeArray<UPromotion*>(Bag->GetArrayField(TEXT("promotions")), Promotions, OuterOwner);
}



