
#include "BeamableCore/Public/AutoGen/AuthV2EmptyMessage.h"




void UAuthV2EmptyMessage::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAuthV2EmptyMessage::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	
}

void UAuthV2EmptyMessage::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
			
}

void UAuthV2EmptyMessage::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	
}



