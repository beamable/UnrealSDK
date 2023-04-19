
#include "BeamableCore/Public/AutoGen/ServiceRoute.h"





void UServiceRoute::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("service"), Service);
	Serializer->WriteValue(TEXT("endpoint"), Endpoint);
	Serializer->WriteValue(TEXT("serviceTypeStr"), UWebhookServiceTypeLibrary::WebhookServiceTypeToSerializationName(ServiceTypeStr));
}

void UServiceRoute::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("service"), Service);
	Serializer->WriteValue(TEXT("endpoint"), Endpoint);
	Serializer->WriteValue(TEXT("serviceTypeStr"), UWebhookServiceTypeLibrary::WebhookServiceTypeToSerializationName(ServiceTypeStr));		
}

void UServiceRoute::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Service = Bag->GetStringField(TEXT("service"));
	Endpoint = Bag->GetStringField(TEXT("endpoint"));
	ServiceTypeStr = UWebhookServiceTypeLibrary::SerializationNameToWebhookServiceType(Bag->GetStringField(TEXT("serviceTypeStr")));
}



