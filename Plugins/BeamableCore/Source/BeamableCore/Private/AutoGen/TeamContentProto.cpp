
#include "BeamableCore/Public/AutoGen/TeamContentProto.h"
#include "Serialization/BeamJsonUtils.h"




void UTeamContentProto::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxPlayers"), &MaxPlayers, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("minPlayers"), &MinPlayers, Serializer);
}

void UTeamContentProto::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxPlayers"), &MaxPlayers, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("minPlayers"), &MinPlayers, Serializer);		
}

void UTeamContentProto::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("name", Bag, Name, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("maxPlayers", Bag, MaxPlayers, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("minPlayers", Bag, MinPlayers, OuterOwner);
}



