
#include "BeamableCore/Public/AutoGen/Team.h"
#include "Serialization/BeamJsonUtils.h"




void UTeam::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("players"), &Players, Serializer);
}

void UTeam::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("players"), &Players, Serializer);		
}

void UTeam::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("name", Bag, Name, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("players", Bag, Players, OuterOwner);
}



