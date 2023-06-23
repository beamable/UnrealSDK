
#include "BeamableCore/Public/AutoGen/LeaveParty.h"
#include "Serialization/BeamJsonUtils.h"




void ULeaveParty::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("playerId"), &PlayerId, Serializer);
}

void ULeaveParty::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("playerId"), &PlayerId, Serializer);		
}

void ULeaveParty::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("playerId", Bag, PlayerId, OuterOwner);
}



