
#include "BeamableCore/Public/AutoGen/SaveTextResponse.h"
#include "Serialization/BeamJsonUtils.h"



void USaveTextResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void USaveTextResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UTextReference*>(TEXT("text"), Text, Serializer);
}

void USaveTextResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UTextReference*>(TEXT("text"), Text, Serializer);		
}

void USaveTextResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UTextReference*>(Bag->GetArrayField(TEXT("text")), Text, OuterOwner);
}



