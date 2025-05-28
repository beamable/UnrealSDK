
#include "BeamableCore/Public/AutoGen/UpdateLobby.h"
#include "Serialization/BeamJsonUtils.h"




void UUpdateLobby::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
	UBeamJsonUtils::SerializeOptional<EBeamLobbyRestriction>(TEXT("restriction"), &Restriction, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamContentId, FString>(TEXT("matchType"), &MatchType, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxPlayers"), &MaxPlayers, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("newHost"), &NewHost, Serializer);
	UBeamJsonUtils::SerializeOptional<UUpdateData*>(TEXT("data"), &Data, Serializer);
}

void UUpdateLobby::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
	UBeamJsonUtils::SerializeOptional<EBeamLobbyRestriction>(TEXT("restriction"), &Restriction, Serializer);
	UBeamJsonUtils::SerializeOptional<FBeamContentId, FString>(TEXT("matchType"), &MatchType, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxPlayers"), &MaxPlayers, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("newHost"), &NewHost, Serializer);
	UBeamJsonUtils::SerializeOptional<UUpdateData*>(TEXT("data"), &Data, Serializer);		
}

void UUpdateLobby::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("name", Bag, Name, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("description", Bag, Description, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<EBeamLobbyRestriction>("restriction", Bag, Restriction, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FBeamContentId, FString>("matchType", Bag, MatchType, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("maxPlayers", Bag, MaxPlayers, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("newHost", Bag, NewHost, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UUpdateData*>("data", Bag, Data, OuterOwner);
}



