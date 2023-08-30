
#include "BeamableCore/Public/AutoGen/ApiPlayersPresencePutPlayerPresenceResponse.h"




void UApiPlayersPresencePutPlayerPresenceResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UApiPlayersPresencePutPlayerPresenceResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	
}

void UApiPlayersPresencePutPlayerPresenceResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
			
}

void UApiPlayersPresencePutPlayerPresenceResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	
}



