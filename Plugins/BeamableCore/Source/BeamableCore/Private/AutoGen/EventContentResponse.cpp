
#include "BeamableCore/Public/AutoGen/EventContentResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UEventContentResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UEventContentResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UEvent*>(TEXT("content"), Content, Serializer);
}

void UEventContentResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UEvent*>(TEXT("content"), Content, Serializer);		
}

void UEventContentResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UEvent*>(TEXT("content"), Bag, Content, OuterOwner);
}



