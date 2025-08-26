
#include "BeamableCore/Public/AutoGen/SaveCatalogRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void USaveCatalogRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UStore*>(TEXT("stores"), Stores, Serializer);
	UBeamJsonUtils::SerializeArray<UOfferDefinition*>(TEXT("offerDefinitions"), OfferDefinitions, Serializer);
}

void USaveCatalogRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UStore*>(TEXT("stores"), Stores, Serializer);
	UBeamJsonUtils::SerializeArray<UOfferDefinition*>(TEXT("offerDefinitions"), OfferDefinitions, Serializer);		
}

void USaveCatalogRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UStore*>(TEXT("stores"), Bag, Stores, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UOfferDefinition*>(TEXT("offerDefinitions"), Bag, OfferDefinitions, OuterOwner);
}



