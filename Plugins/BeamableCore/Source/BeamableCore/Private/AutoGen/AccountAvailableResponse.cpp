
#include "BeamableCore/Public/AutoGen/AccountAvailableResponse.h"




void UAccountAvailableResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAccountAvailableResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("available"), bAvailable);
}

void UAccountAvailableResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("available"), bAvailable);		
}

void UAccountAvailableResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bAvailable = Bag->GetBoolField(TEXT("available"));
}



