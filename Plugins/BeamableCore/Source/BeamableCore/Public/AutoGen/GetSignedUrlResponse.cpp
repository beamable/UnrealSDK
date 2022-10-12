
#include "AutoGen/GetSignedUrlResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UGetSignedUrlResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UGetLogsUrlHeader*>(TEXT("headers"), Headers, Serializer);
	Serializer->WriteValue(TEXT("url"), Url);
	Serializer->WriteValue(TEXT("body"), Body);
	Serializer->WriteValue(TEXT("method"), Method);
}

void UGetSignedUrlResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UGetLogsUrlHeader*>(TEXT("headers"), Headers, Serializer);
	Serializer->WriteValue(TEXT("url"), Url);
	Serializer->WriteValue(TEXT("body"), Body);
	Serializer->WriteValue(TEXT("method"), Method);		
}

void UGetSignedUrlResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UGetLogsUrlHeader*>(Bag->GetArrayField(TEXT("headers")), Headers, OuterOwner);
	Url = Bag->GetStringField(TEXT("url"));
	Body = Bag->GetStringField(TEXT("body"));
	Method = Bag->GetStringField(TEXT("method"));
}