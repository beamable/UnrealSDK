
#include "BeamableCore/Public/AutoGen/MailResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UMailResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UMailResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<UMessage*>(TEXT("result"), &Result, Serializer);
}

void UMailResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<UMessage*>(TEXT("result"), &Result, Serializer);		
}

void UMailResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<UMessage*>("result", Bag, Result, OuterOwner);
}



