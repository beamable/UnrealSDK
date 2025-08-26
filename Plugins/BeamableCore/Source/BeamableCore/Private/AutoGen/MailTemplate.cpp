
#include "BeamableCore/Public/AutoGen/MailTemplate.h"




void UMailTemplate::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UMailTemplate::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("subject"), Subject, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("body"), Body, Serializer);
}

void UMailTemplate::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("subject"), Subject, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("body"), Body, Serializer);		
}

void UMailTemplate::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("subject"), Bag, Subject);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("body"), Bag, Body);
}



