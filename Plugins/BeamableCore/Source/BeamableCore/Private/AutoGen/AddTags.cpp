
#include "BeamableCore/Public/AutoGen/AddTags.h"
#include "Serialization/BeamJsonUtils.h"




void UAddTags::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamGamerTag, FString>(TEXT("playerId"), &PlayerId, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("replace"), &bReplace, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamTag>, FBeamTag>(TEXT("tags"), &Tags, Serializer);
}

void UAddTags::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FBeamGamerTag, FString>(TEXT("playerId"), &PlayerId, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("replace"), &bReplace, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamTag>, FBeamTag>(TEXT("tags"), &Tags, Serializer);		
}

void UAddTags::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FBeamGamerTag, FString>("playerId", Bag, PlayerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("replace", Bag, bReplace, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FBeamTag>, FBeamTag>("tags", Bag, Tags, OuterOwner);
}



