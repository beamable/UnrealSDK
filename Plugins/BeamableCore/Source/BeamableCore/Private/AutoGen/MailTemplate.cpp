
#include "BeamableCore/Public/AutoGen/MailTemplate.h"




void UMailTemplate::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UMailTemplate::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("subject"), Subject);
	Serializer->WriteValue(TEXT("body"), Body);
}

void UMailTemplate::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("subject"), Subject);
	Serializer->WriteValue(TEXT("body"), Body);		
}

void UMailTemplate::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Subject = Bag->GetStringField(TEXT("subject"));
	Body = Bag->GetStringField(TEXT("body"));
}



