
#include "BeamableCore/Public/AutoGen/EmptyMessage.h"




void UEmptyMessage::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UEmptyMessage::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	
}

void UEmptyMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
			
}

void UEmptyMessage::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	
}



