
#include "BeamableCore/Public/AutoGen/SaveContentResponse.h"
#include "Serialization/BeamJsonUtils.h"



void USaveContentResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void USaveContentResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UContentReference*>(TEXT("content"), Content, Serializer);
}

void USaveContentResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UContentReference*>(TEXT("content"), Content, Serializer);		
}

void USaveContentResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UContentReference*>(Bag->GetArrayField(TEXT("content")), Content, OuterOwner);
}



