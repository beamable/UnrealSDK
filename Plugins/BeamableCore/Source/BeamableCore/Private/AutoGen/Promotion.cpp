
#include "BeamableCore/Public/AutoGen/Promotion.h"
#include "Serialization/BeamJsonUtils.h"




void UPromotion::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeUObject<UPromotable*>("source", Source, Serializer);
	UBeamJsonUtils::SerializeUObject<UPromotable*>("destination", Destination, Serializer);
}

void UPromotion::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeUObject<UPromotable*>("source", Source, Serializer);
	UBeamJsonUtils::SerializeUObject<UPromotable*>("destination", Destination, Serializer);		
}

void UPromotion::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Id = Bag->GetStringField(TEXT("id"));
	UBeamJsonUtils::DeserializeUObject<UPromotable*>("source", Bag, Source, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<UPromotable*>("destination", Bag, Destination, OuterOwner);
}



