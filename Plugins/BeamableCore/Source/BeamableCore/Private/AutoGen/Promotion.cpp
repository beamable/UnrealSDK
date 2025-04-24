
#include "BeamableCore/Public/AutoGen/Promotion.h"
#include "Serialization/BeamJsonUtils.h"




void UPromotion::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeUObject<UPromotable*>("source", Source, Serializer);
	UBeamJsonUtils::SerializeUObject<UPromotable*>("destination", Destination, Serializer);
}

void UPromotion::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeUObject<UPromotable*>("source", Source, Serializer);
	UBeamJsonUtils::SerializeUObject<UPromotable*>("destination", Destination, Serializer);		
}

void UPromotion::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeUObject<UPromotable*>("source", Bag, Source, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<UPromotable*>("destination", Bag, Destination, OuterOwner);
}



