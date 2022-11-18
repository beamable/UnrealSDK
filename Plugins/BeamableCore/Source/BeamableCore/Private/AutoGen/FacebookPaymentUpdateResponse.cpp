
#include "AutoGen/FacebookPaymentUpdateResponse.h"




void UFacebookPaymentUpdateResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UFacebookPaymentUpdateResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), Result);
	Serializer->WriteValue(TEXT("contentType"), ContentType);
}

void UFacebookPaymentUpdateResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("result"), Result);
	Serializer->WriteValue(TEXT("contentType"), ContentType);		
}

void UFacebookPaymentUpdateResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Result = Bag->GetStringField(TEXT("result"));
	ContentType = Bag->GetStringField(TEXT("contentType"));
}