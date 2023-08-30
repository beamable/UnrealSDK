
#include "BeamableCore/Public/AutoGen/ApiMailboxPublishPostMailboxResponse.h"




void UApiMailboxPublishPostMailboxResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UApiMailboxPublishPostMailboxResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	
}

void UApiMailboxPublishPostMailboxResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
			
}

void UApiMailboxPublishPostMailboxResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	
}



