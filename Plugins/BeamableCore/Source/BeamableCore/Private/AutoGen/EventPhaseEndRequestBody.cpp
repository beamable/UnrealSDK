
#include "BeamableCore/Public/AutoGen/EventPhaseEndRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UEventPhaseEndRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("time"), &Time, Serializer);
}

void UEventPhaseEndRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("time"), &Time, Serializer);		
}

void UEventPhaseEndRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("time", Bag, Time, OuterOwner);
}



