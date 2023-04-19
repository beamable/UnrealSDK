
#include "BeamableCore/Public/AutoGen/OfferRequirement.h"
#include "Serialization/BeamJsonUtils.h"




void UOfferRequirement::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("offerSymbol"), OfferSymbol);
	UBeamJsonUtils::SerializeUObject<UOfferConstraint*>("purchases", Purchases, Serializer);
}

void UOfferRequirement::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("offerSymbol"), OfferSymbol);
	UBeamJsonUtils::SerializeUObject<UOfferConstraint*>("purchases", Purchases, Serializer);		
}

void UOfferRequirement::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	OfferSymbol = Bag->GetStringField(TEXT("offerSymbol"));
	UBeamJsonUtils::DeserializeUObject<UOfferConstraint*>("purchases", Bag, Purchases, OuterOwner);
}



