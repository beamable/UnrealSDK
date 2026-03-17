
#include "BeamableCore/Public/AutoGen/ApiSessionsHeartbeatPostSessionResponse.h"




void UApiSessionsHeartbeatPostSessionResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UApiSessionsHeartbeatPostSessionResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	
}

void UApiSessionsHeartbeatPostSessionResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
			
}

void UApiSessionsHeartbeatPostSessionResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	
}



