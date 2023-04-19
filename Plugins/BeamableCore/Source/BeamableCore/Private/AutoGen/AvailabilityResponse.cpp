
#include "BeamableCore/Public/AutoGen/AvailabilityResponse.h"




void UAvailabilityResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAvailabilityResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), bName);
	Serializer->WriteValue(TEXT("tag"), bTag);
}

void UAvailabilityResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), bName);
	Serializer->WriteValue(TEXT("tag"), bTag);		
}

void UAvailabilityResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bName = Bag->GetBoolField(TEXT("name"));
	bTag = Bag->GetBoolField(TEXT("tag"));
}



