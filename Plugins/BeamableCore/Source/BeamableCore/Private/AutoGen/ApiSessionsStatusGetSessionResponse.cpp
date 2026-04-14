
#include "BeamableCore/Public/AutoGen/ApiSessionsStatusGetSessionResponse.h"




void UApiSessionsStatusGetSessionResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UApiSessionsStatusGetSessionResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	
}

void UApiSessionsStatusGetSessionResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
			
}

void UApiSessionsStatusGetSessionResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	
}



