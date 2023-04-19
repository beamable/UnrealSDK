
#include "BeamableCore/Public/AutoGen/PlayerStatusUpdate.h"
#include "Serialization/BeamJsonUtils.h"




void UPlayerStatusUpdate::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("tier"), &Tier, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("stage"), &Stage, Serializer);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("score"), &Score, Serializer);
}

void UPlayerStatusUpdate::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("tier"), &Tier, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("stage"), &Stage, Serializer);
	UBeamJsonUtils::SerializeOptional<double>(TEXT("score"), &Score, Serializer);		
}

void UPlayerStatusUpdate::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int32>("tier", Bag, Tier, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("stage", Bag, Stage, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<double>("score", Bag, Score, OuterOwner);
}



