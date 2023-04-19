
#include "BeamableCore/Public/AutoGen/MicroserviceSecretResponse.h"




void UMicroserviceSecretResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UMicroserviceSecretResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("secret"), Secret);
}

void UMicroserviceSecretResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("secret"), Secret);		
}

void UMicroserviceSecretResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Secret = Bag->GetStringField(TEXT("secret"));
}



