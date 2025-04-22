
#include "BeamableCore/Public/AutoGen/PingRsp.h"




void UPingRsp::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UPingRsp::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("keepAlive"), bKeepAlive, Serializer);
}

void UPingRsp::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("keepAlive"), bKeepAlive, Serializer);		
}

void UPingRsp::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("keepAlive")), bKeepAlive);
}



