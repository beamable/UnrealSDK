
#include "BeamableCore/Public/AutoGen/AddTags.h"
#include "Serialization/BeamJsonUtils.h"




void UAddTags::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("playerId"), &PlayerId, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("replace"), &bReplace, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UTag*>, UTag*>(TEXT("tags"), &Tags, Serializer);
}

void UAddTags::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("playerId"), &PlayerId, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("replace"), &bReplace, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UTag*>, UTag*>(TEXT("tags"), &Tags, Serializer);		
}

void UAddTags::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("playerId", Bag, PlayerId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("replace", Bag, bReplace, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UTag*>, UTag*>("tags", Bag, Tags, OuterOwner);
}



