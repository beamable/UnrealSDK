
#include "BeamableCore/Public/AutoGen/RealmPromotion.h"
#include "Serialization/BeamJsonUtils.h"




void URealmPromotion::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeUObject<UPromotable*>("source", Source, Serializer);
	UBeamJsonUtils::SerializeUObject<UPromotable*>("destination", Destination, Serializer);
}

void URealmPromotion::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeUObject<UPromotable*>("source", Source, Serializer);
	UBeamJsonUtils::SerializeUObject<UPromotable*>("destination", Destination, Serializer);		
}

void URealmPromotion::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	UBeamJsonUtils::DeserializeUObject<UPromotable*>("source", Bag, Source, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<UPromotable*>("destination", Bag, Destination, OuterOwner);
}



