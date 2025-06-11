
#include "BeamableCore/Public/AutoGen/SessionHeartbeat.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void USessionHeartbeat::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void USessionHeartbeat::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gt"), Gt, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("heartbeat"), &Heartbeat, Serializer);
}

void USessionHeartbeat::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gt"), Gt, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("heartbeat"), &Heartbeat, Serializer);		
}

void USessionHeartbeat::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("gt")), Gt);
	UBeamJsonUtils::DeserializeOptional<int64>("heartbeat", Bag, Heartbeat, OuterOwner);
}



