
#include "BeamableCore/Public/AutoGen/Catalog.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UCatalog::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("version"), Version, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);
	UBeamJsonUtils::SerializeArray<UStore*>(TEXT("stores"), Stores, Serializer);
	UBeamJsonUtils::SerializeArray<UOfferDefinition*>(TEXT("offerDefinitions"), OfferDefinitions, Serializer);
}

void UCatalog::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("version"), Version, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);
	UBeamJsonUtils::SerializeArray<UStore*>(TEXT("stores"), Stores, Serializer);
	UBeamJsonUtils::SerializeArray<UOfferDefinition*>(TEXT("offerDefinitions"), OfferDefinitions, Serializer);		
}

void UCatalog::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("version")), Version);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("created")), Created);
	UBeamJsonUtils::DeserializeArray<UStore*>(Bag->GetArrayField(TEXT("stores")), Stores, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UOfferDefinition*>(Bag->GetArrayField(TEXT("offerDefinitions")), OfferDefinitions, OuterOwner);
}



