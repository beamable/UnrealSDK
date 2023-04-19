
#include "BeamableCore/Public/AutoGen/ListTokenResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UListTokenResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UListTokenResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UListTokenResponseItem*>(TEXT("items"), Items, Serializer);
}

void UListTokenResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UListTokenResponseItem*>(TEXT("items"), Items, Serializer);		
}

void UListTokenResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UListTokenResponseItem*>(Bag->GetArrayField(TEXT("items")), Items, OuterOwner);
}



