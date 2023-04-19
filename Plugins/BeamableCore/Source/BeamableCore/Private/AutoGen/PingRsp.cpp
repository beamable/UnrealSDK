
#include "BeamableCore/Public/AutoGen/PingRsp.h"




void UPingRsp::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UPingRsp::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("keepAlive"), bKeepAlive);
}

void UPingRsp::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("keepAlive"), bKeepAlive);		
}

void UPingRsp::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bKeepAlive = Bag->GetBoolField(TEXT("keepAlive"));
}



