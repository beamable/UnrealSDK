
#include "BeamableCore/Public/AutoGen/GetCatalogResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetCatalogResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetCatalogResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<UCatalog*>(TEXT("catalog"), &Catalog, Serializer);
}

void UGetCatalogResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<UCatalog*>(TEXT("catalog"), &Catalog, Serializer);		
}

void UGetCatalogResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<UCatalog*>("catalog", Bag, Catalog, OuterOwner);
}



