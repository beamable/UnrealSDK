
#include "BeamableCore/Public/AutoGen/RemoveTags.h"
#include "Serialization/BeamJsonUtils.h"




void URemoveTags::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamGamerTag, FString>(TEXT("playerId"), &PlayerId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);
}

void URemoveTags::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamGamerTag, FString>(TEXT("playerId"), &PlayerId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("tags"), &Tags, Serializer);		
}

void URemoveTags::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FBeamGamerTag, FString>("playerId", Bag, PlayerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("tags", Bag, Tags, OuterOwner);
}



