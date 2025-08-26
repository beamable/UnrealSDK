
#include "BeamableCore/Public/AutoGen/ObjectId.h"
#include "Serialization/BeamJsonUtils.h"




void UObjectId::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("timestamp"), &Timestamp, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("creationTime"), &CreationTime, Serializer);
}

void UObjectId::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("timestamp"), &Timestamp, Serializer);
	UBeamJsonUtils::SerializeOptional<FDateTime>(TEXT("creationTime"), &CreationTime, Serializer);		
}

void UObjectId::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int32>("timestamp", Bag, Timestamp, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FDateTime>("creationTime", Bag, CreationTime, OuterOwner);
}



