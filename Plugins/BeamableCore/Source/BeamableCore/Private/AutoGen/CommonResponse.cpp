
#include "BeamableCore/Public/AutoGen/CommonResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UCommonResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UCommonResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("result"), Result, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("data"), Data, Serializer);
}

void UCommonResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("result"), Result, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("data"), Data, Serializer);		
}

void UCommonResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("result")), Result);
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("data")), Data, OuterOwner);
}



