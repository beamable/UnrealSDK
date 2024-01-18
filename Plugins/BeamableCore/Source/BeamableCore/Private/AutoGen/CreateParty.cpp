
#include "BeamableCore/Public/AutoGen/CreateParty.h"
#include "Serialization/BeamJsonUtils.h"




void UCreateParty::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("restriction"), &Restriction, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamGamerTag, FString>(TEXT("leader"), &Leader, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxSize"), &MaxSize, Serializer);
}

void UCreateParty::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("restriction"), &Restriction, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamGamerTag, FString>(TEXT("leader"), &Leader, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxSize"), &MaxSize, Serializer);		
}

void UCreateParty::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("restriction", Bag, Restriction, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamGamerTag, FString>("leader", Bag, Leader, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("maxSize", Bag, MaxSize, OuterOwner);
}



