
#include "BeamableCore/Public/AutoGen/EmptyRsp.h"




void UEmptyRsp::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UEmptyRsp::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	
}

void UEmptyRsp::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
			
}

void UEmptyRsp::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	
}



