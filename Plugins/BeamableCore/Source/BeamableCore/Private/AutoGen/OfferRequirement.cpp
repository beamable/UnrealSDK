
#include "BeamableCore/Public/AutoGen/OfferRequirement.h"
#include "Serialization/BeamJsonUtils.h"




void UOfferRequirement::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("offerSymbol"), OfferSymbol, Serializer);
	UBeamJsonUtils::SerializeUObject<UOfferConstraint*>("purchases", Purchases, Serializer);
}

void UOfferRequirement::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("offerSymbol"), OfferSymbol, Serializer);
	UBeamJsonUtils::SerializeUObject<UOfferConstraint*>("purchases", Purchases, Serializer);		
}

void UOfferRequirement::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("offerSymbol")), OfferSymbol);
	UBeamJsonUtils::DeserializeUObject<UOfferConstraint*>("purchases", Bag, Purchases, OuterOwner);
}



