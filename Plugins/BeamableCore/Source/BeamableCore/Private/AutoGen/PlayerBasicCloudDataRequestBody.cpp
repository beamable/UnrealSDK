
#include "BeamableCore/Public/AutoGen/PlayerBasicCloudDataRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UPlayerBasicCloudDataRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("playerId"), &PlayerId, Serializer);
}

void UPlayerBasicCloudDataRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("playerId"), &PlayerId, Serializer);		
}

void UPlayerBasicCloudDataRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int64>("playerId", Bag, PlayerId, OuterOwner);
}



