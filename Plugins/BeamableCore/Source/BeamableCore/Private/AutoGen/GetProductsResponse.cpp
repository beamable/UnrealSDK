
#include "BeamableCore/Public/AutoGen/GetProductsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetProductsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetProductsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UProductView*>(TEXT("products"), Products, Serializer);
}

void UGetProductsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UProductView*>(TEXT("products"), Products, Serializer);		
}

void UGetProductsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UProductView*>(Bag->GetArrayField(TEXT("products")), Products, OuterOwner);
}



