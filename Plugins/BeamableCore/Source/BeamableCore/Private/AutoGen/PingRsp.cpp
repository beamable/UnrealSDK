
#include "AutoGen/PingRsp.h"



void UPingRsp ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("keepAlive"), bKeepAlive);
}

void UPingRsp::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("keepAlive"), bKeepAlive);		
}

void UPingRsp ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bKeepAlive = Bag->GetBoolField(TEXT("keepAlive"));
}