
#include "BeamableCore/Public/AutoGen/ListMailCategoriesResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UListMailCategoriesResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UListMailCategoriesResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(TEXT("result"), Result, Serializer);
}

void UListMailCategoriesResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(TEXT("result"), Result, Serializer);		
}

void UListMailCategoriesResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("result")), Result, OuterOwner);
}



