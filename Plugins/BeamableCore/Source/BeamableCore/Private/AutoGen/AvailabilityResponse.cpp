
#include "BeamableCore/Public/AutoGen/AvailabilityResponse.h"




void UAvailabilityResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAvailabilityResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), bName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tag"), bTag, Serializer);
}

void UAvailabilityResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), bName, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tag"), bTag, Serializer);		
}

void UAvailabilityResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), bName);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("tag")), bTag);
}



