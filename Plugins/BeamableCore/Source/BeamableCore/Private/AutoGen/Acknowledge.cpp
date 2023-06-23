
#include "BeamableCore/Public/AutoGen/Acknowledge.h"




void UAcknowledge::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAcknowledge::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	
}

void UAcknowledge::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
			
}

void UAcknowledge::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	
}



