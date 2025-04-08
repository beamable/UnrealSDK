
#include "BeamableCore/Public/AutoGen/GetSignedUrlResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetSignedUrlResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetSignedUrlResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("url"), Url);
	Serializer->WriteValue(TEXT("body"), Body);
	Serializer->WriteValue(TEXT("method"), Method);
	UBeamJsonUtils::SerializeArray<UGetLogsUrlHeader*>(TEXT("headers"), Headers, Serializer);
}

void UGetSignedUrlResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("url"), Url);
	Serializer->WriteValue(TEXT("body"), Body);
	Serializer->WriteValue(TEXT("method"), Method);
	UBeamJsonUtils::SerializeArray<UGetLogsUrlHeader*>(TEXT("headers"), Headers, Serializer);		
}

void UGetSignedUrlResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("url")), Url);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("body")), Body);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("method")), Method);
	UBeamJsonUtils::DeserializeArray<UGetLogsUrlHeader*>(Bag->GetArrayField(TEXT("headers")), Headers, OuterOwner);
}



