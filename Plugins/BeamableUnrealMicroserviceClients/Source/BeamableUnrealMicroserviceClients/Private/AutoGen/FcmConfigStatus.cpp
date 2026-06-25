
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/FcmConfigStatus.h"




void UFcmConfigStatus::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UFcmConfigStatus::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("configured"), bConfigured, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("privateKeyLoaded"), bPrivateKeyLoaded, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("projectId"), ProjectId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("clientEmail"), ClientEmail, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tokenUri"), TokenUri, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);
}

void UFcmConfigStatus::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("configured"), bConfigured, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("privateKeyLoaded"), bPrivateKeyLoaded, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("projectId"), ProjectId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("clientEmail"), ClientEmail, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tokenUri"), TokenUri, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("message"), Message, Serializer);		
}

void UFcmConfigStatus::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("configured"), Bag, bConfigured);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("privateKeyLoaded"), Bag, bPrivateKeyLoaded);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("projectId"), Bag, ProjectId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("clientEmail"), Bag, ClientEmail);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("tokenUri"), Bag, TokenUri);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("message"), Bag, Message);
}



