
#include "BeamableCore/Public/AutoGen/ApiSessionsPostSessionResponse.h"




void UApiSessionsPostSessionResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UApiSessionsPostSessionResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	
}

void UApiSessionsPostSessionResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
			
}

void UApiSessionsPostSessionResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	
}



