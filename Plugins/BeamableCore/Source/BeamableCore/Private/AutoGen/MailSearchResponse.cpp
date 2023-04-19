
#include "BeamableCore/Public/AutoGen/MailSearchResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UMailSearchResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UMailSearchResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UMailSearchResponseClause*>(TEXT("results"), Results, Serializer);
}

void UMailSearchResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UMailSearchResponseClause*>(TEXT("results"), Results, Serializer);		
}

void UMailSearchResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UMailSearchResponseClause*>(Bag->GetArrayField(TEXT("results")), Results, OuterOwner);
}



